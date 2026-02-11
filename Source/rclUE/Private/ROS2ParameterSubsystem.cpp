#include "ROS2NodeSubsystem.h"
#include "Engine/GameInstance.h"

#include "Async/Async.h"
#include <type_traits>

#include "ROS2ParameterSubsystem.h"


DEFINE_LOG_CATEGORY(LogROS2ParameterSubsystem);

bool on_parameter_changed(const Parameter * old_param, const Parameter * new_param, void * context)
{
    UROS2ParameterSubsystem* ParamSubsystem = static_cast<UROS2ParameterSubsystem*>(context);

    if (old_param == nullptr && new_param == nullptr) {
        UE_LOG(LogROS2ParameterSubsystem, Error, TEXT("Callback error, both parameters are nullptr"));
        return false;
    }
    
    const TWeakObjectPtr<UROS2ParameterSubsystem> ParamSubsystemWeakPtr(ParamSubsystem);

    if (new_param != nullptr)
    {
        FString NewParamName = StringCast<TCHAR>(old_param->name.data).Get();
        UE_LOG(LogROS2ParameterSubsystem, Verbose, TEXT("Parameter '%s' modified"), *NewParamName);
        const FROS2Parameter* UpdatedParamPtr = ParamSubsystem->UpdateParameterInternal(*new_param);
        
        const FROS2Parameter UpdatedParamValue = *UpdatedParamPtr;
        const bool bIsCreate = (old_param == nullptr);

        AsyncTask(ENamedThreads::GameThread, [ParamSubsystemWeakPtr, UpdatedParamValue, bIsCreate, NewParamName]()
        {
            if (!ParamSubsystemWeakPtr.IsValid())
            {
                return;
            }

            auto* Subsystem = ParamSubsystemWeakPtr.Get();
            if (bIsCreate)
            {
                UE_LOG(LogROS2ParameterSubsystem, Display, TEXT("Creating parameter '%s'"), *NewParamName);
                Subsystem->OnParameterAdded.Broadcast(UpdatedParamValue);
            }

            Subsystem->OnParameterChanged.Broadcast(UpdatedParamValue);
        });
    } else
    {
        FString ParamName = StringCast<TCHAR>(old_param->name.data).Get();
        UE_LOG(LogROS2ParameterSubsystem, Display, TEXT("Deleting parameter '%s'"), *ParamName);
        
        AsyncTask(ENamedThreads::GameThread, [ParamSubsystemWeakPtr, ParamName]()
        {
            if (!ParamSubsystemWeakPtr.IsValid())
            {
                return;
            }
            ParamSubsystemWeakPtr->OnParameterDeleted.Broadcast(ParamName);
        });
    }
    
    return true;
}

bool UROS2ParameterSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    return true;
}

void UROS2ParameterSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Collection.InitializeDependency<UROS2NodeSubsystem>();
    Super::Initialize(Collection);
    
    UROS2NodeSubsystem* NodeSubsystem = GetGameInstance()->GetSubsystem<UROS2NodeSubsystem>();
    rclc_parameter_server_init_default(&param_server, NodeSubsystem->GetRCLNode());
    
    UROS2Subsystem * R2Subsystem = GetGameInstance()->GetSubsystem<UROS2Subsystem>();
    
    rclc_executor_init(
      &executor, &R2Subsystem->GetSupport()->Get().context, RCLC_EXECUTOR_PARAMETER_SERVER_HANDLES + 1,
      R2Subsystem->AllocatorPtr());
    rclc_executor_add_parameter_server_with_context(&executor, &param_server, on_parameter_changed, this);
    
    bIsInitialized = true;
    UE_LOG(LogROS2ParameterSubsystem, Display, TEXT("Initialised parameter server on node '%s'"), *NodeSubsystem->Name);
}

void UROS2ParameterSubsystem::Deinitialize()
{
    FScopeLock Lock(&Mutex);

    bIsInitialized = false;

    UROS2NodeSubsystem* NodeSubsystem = GetGameInstance()->GetSubsystem<UROS2NodeSubsystem>();
    bool bNodeValid = IsValid(NodeSubsystem) && NodeSubsystem->State == UROS2State::Initialized;

    // rclc_executor_fini destroys its internal wait set via the RMW layer,
    // which requires a valid RCL context. Only safe to call if the node
    // (and therefore the context) is still alive.
    if (bNodeValid)
    {
        rclc_executor_fini(&executor);
        rclc_parameter_server_fini(&param_server, NodeSubsystem->GetRCLNode());
        UE_LOG(LogROS2ParameterSubsystem, Display, TEXT("Destroyed parameter server on node '%s'"), *NodeSubsystem->Name);
    }
    else
    {
        UE_LOG(LogROS2ParameterSubsystem, Warning, TEXT("Skipping parameter subsystem fini - node already destroyed"));
    }

    Super::Deinitialize();
}

void UROS2ParameterSubsystem::AddParameter(const FROS2Parameter& Parameter)
{
    FScopeLock Lock(&Mutex);
    ParametersCache.Add(Parameter.Name, Parameter);
    
    rclc_add_parameter(&param_server, StringCast<ANSICHAR>(*Parameter.Name).Get(), ParameterType_LUT[Parameter.Type]);
    rclc_add_parameter_description(&param_server, StringCast<ANSICHAR>(*Parameter.Name).Get(),
        StringCast<ANSICHAR>(*Parameter.Description).Get(), StringCast<ANSICHAR>(*Parameter.AdditionalConstraints).Get());
    rclc_set_parameter_read_only(&param_server, StringCast<ANSICHAR>(*Parameter.Name).Get(), Parameter.ReadOnly);
    UE_LOG(LogROS2ParameterSubsystem, Display, TEXT("Added parameter '%s'"), *Parameter.Name);

    UpdateParameter(Parameter);
}

void UROS2ParameterSubsystem::DeleteParameter(const FROS2Parameter& Parameter)
{
    DeleteParameterByName(Parameter.Name);
}

void UROS2ParameterSubsystem::DeleteParameterByName(const FString& ParameterName)
{
    FScopeLock Lock(&Mutex);
    rclc_delete_parameter(&param_server, StringCast<ANSICHAR>(*ParameterName).Get());
    ParametersCache.Remove(ParameterName);
}

void UROS2ParameterSubsystem::UpdateParameter(const FROS2Parameter& Param)
{
    FScopeLock Lock(&Mutex);
    switch (Param.Type) {
    case UParameterType::Boolean:
        rclc_parameter_set_bool(&param_server, StringCast<ANSICHAR>(*Param.Name).Get(), Param.Value.Get<bool>());
        break;
    case UParameterType::Integer:
        rclc_parameter_set_int(&param_server, StringCast<ANSICHAR>(*Param.Name).Get(), Param.Value.Get<int64>());
        break;
    case UParameterType::Double:
        rclc_parameter_set_double(&param_server, StringCast<ANSICHAR>(*Param.Name).Get(), Param.Value.Get<double>());
        break;
    default:
        UE_LOG(LogROS2ParameterSubsystem, Error, TEXT("Unsupported param type in update of '%s'"), *Param.Name);
        return;
    }
}

FROS2Parameter* UROS2ParameterSubsystem::UpdateParameterInternal(const Parameter& NewParam)
{
    FScopeLock Lock(&Mutex);
    FString ParamName = StringCast<TCHAR>(NewParam.name.data).Get();
    if (ParametersCache.Contains(ParamName))
    {
        auto CachedParamPtr = ParametersCache.Find(ParamName);
        
        FROS2Parameter& CachedParam = *CachedParamPtr;
        switch (NewParam.value.type) {
        case RCLC_PARAMETER_BOOL:
            CachedParam.Type = UParameterType::Boolean;
            CachedParam.Value.Set<bool>(NewParam.value.bool_value);
            break;
        case RCLC_PARAMETER_INT:
            CachedParam.Type = UParameterType::Integer;
            CachedParam.Value.Set<int64>(NewParam.value.integer_value);
            break;
        case RCLC_PARAMETER_DOUBLE:
            CachedParam.Type = UParameterType::Double;
            CachedParam.Value.Set<double>(NewParam.value.double_value);
            break;
        default:
            UE_LOG(LogROS2ParameterSubsystem, Error, TEXT("Unsupported param type in update of '%s'"), *ParamName);
            return nullptr;
        }
        
        return CachedParamPtr;
    }
    UE_LOG(LogROS2ParameterSubsystem, Error, TEXT("Param '%s' not found"), *ParamName);
    return nullptr;
}

void UROS2ParameterSubsystem::Tick(float DeltaTime)
{
    if (!bIsInitialized)
    {
        return;
    }
    rclc_executor_spin_some(&executor, 0);
}

bool UROS2ParameterSubsystem::IsTickable() const
{
    return true;
}

bool UROS2ParameterSubsystem::IsTickableWhenPaused() const
{
    return false;
}

bool UROS2ParameterSubsystem::IsTickableInEditor() const
{
    return false;
}

TStatId UROS2ParameterSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UROS2ParameterSubsystem, STATGROUP_Tickables);
}

FROS2Parameter UROS2ParameterSubsystem::GetParameterByName(const FString& Name)
{
    auto Param = ParametersCache.Find(Name);
    
    if (Param != nullptr)
    {
        return *Param;
    }
    return FROS2Parameter();
}

bool UROS2ParameterBlueprintLibrary::GetBooleanParameter(const FROS2Parameter& Param)
{
    if (Param.Value.IsType<bool>())
    {
        return Param.Value.Get<bool>();
    }
    return false;
}

int64 UROS2ParameterBlueprintLibrary::GetIntegerParameter(const FROS2Parameter& Param)
{
    if (Param.Value.IsType<int64>())
    {
        return Param.Value.Get<int64>();
    }
    return 0;
}

double UROS2ParameterBlueprintLibrary::GetDoubleParameter(const FROS2Parameter& Param)
{
    if (Param.Value.IsType<double>())
    {
        return Param.Value.Get<double>();
    }
    return 0.0;
}

FROS2Parameter& UROS2ParameterBlueprintLibrary::SetBooleanParameter(FROS2Parameter& Param, bool InValue)
{
    Param.Type = UParameterType::Boolean;
    Param.Value.Set<bool>(InValue);
    return Param;
}

FROS2Parameter& UROS2ParameterBlueprintLibrary::SetIntegerParameter(FROS2Parameter& Param, int64 InValue)
{
    Param.Type = UParameterType::Integer;
    Param.Value.Set<int64>(InValue);
    return Param;
}

FROS2Parameter& UROS2ParameterBlueprintLibrary::SetDoubleParameter(FROS2Parameter& Param, double InValue)
{
    Param.Type = UParameterType::Double;
    Param.Value.Set<double>(InValue);
    return Param;
}