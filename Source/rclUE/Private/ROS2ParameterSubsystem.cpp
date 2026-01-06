#include "ROS2NodeSubsystem.h"
#include "Engine/GameInstance.h"

#include "ROS2ParameterSubsystem.h"

#include "Async/Async.h"

DEFINE_LOG_CATEGORY(LogROS2ParameterSubsystem);

bool on_parameter_changed(const Parameter * old_param, const Parameter * new_param, void * context)
{
    UROS2ParameterSubsystem* ParamSubsystem = static_cast<UROS2ParameterSubsystem*>(context);

    if (old_param == nullptr && new_param == nullptr) {
        UE_LOG(LogROS2ParameterSubsystem, Error, TEXT("Callback error, both parameters are nullptr"));
        return false;
    }

    if (new_param != nullptr)
    {
        FString NewParamName = StringCast<TCHAR>(old_param->name.data).Get();
        UE_LOG(LogROS2ParameterSubsystem, Verbose, TEXT("Parameter %s modified"), *NewParamName);
        FROS2Parameter* Param = ParamSubsystem->UpdateParameterInternal(*new_param);

        if (old_param == nullptr) {
            UE_LOG(LogROS2ParameterSubsystem, Verbose, TEXT("Creating new parameter %s"), *NewParamName);
            ParamSubsystem->OnParameterAdded.Broadcast(*Param);
        }
        
        Async(EAsyncExecution::TaskGraph, [ParamSubsystemWeakPtr = TWeakObjectPtr<UROS2ParameterSubsystem>(ParamSubsystem), Param]()
        {
            if (!ParamSubsystemWeakPtr.IsValid())
                return;
            ParamSubsystemWeakPtr->OnParameterChanged.Broadcast(*Param);
        });
    } else
    {
        FString ParamName = StringCast<TCHAR>(old_param->name.data).Get();
        UE_LOG(LogROS2ParameterSubsystem, Verbose, TEXT("Deleting parameter %s"), *ParamName);
        ParamSubsystem->OnParameterDeleted.Broadcast(ParamName);
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
    
    UROS2NodeSubsystem* Node = GetGameInstance()->GetSubsystem<UROS2NodeSubsystem>();
    rclc_parameter_server_init_default(&param_server, Node->GetRCLNode());
    
    UROS2Subsystem * R2Subsystem = GetGameInstance()->GetSubsystem<UROS2Subsystem>();
    
    rclc_executor_init(
      &executor, &R2Subsystem->GetSupport()->Get().context, RCLC_EXECUTOR_PARAMETER_SERVER_HANDLES + 1,
      R2Subsystem->AllocatorPtr());
    rclc_executor_add_parameter_server_with_context(&executor, &param_server, on_parameter_changed, this);
}

void UROS2ParameterSubsystem::Deinitialize()
{
    UROS2NodeSubsystem* Node = GetGameInstance()->GetSubsystem<UROS2NodeSubsystem>();
    rclc_executor_fini(&executor);
    rclc_parameter_server_fini(&param_server, Node->GetRCLNode());
    
    Super::Deinitialize();
}

void UROS2ParameterSubsystem::AddParameter(const FROS2Parameter& Parameter)
{
    rclc_add_parameter(&param_server, StringCast<ANSICHAR>(*Parameter.Name).Get(), ParameterType_LUT[Parameter.Type]);
    rclc_add_parameter_description(&param_server, StringCast<ANSICHAR>(*Parameter.Name).Get(),
        StringCast<ANSICHAR>(*Parameter.Description).Get(), StringCast<ANSICHAR>(*Parameter.AdditionalConstraints).Get());
    rclc_set_parameter_read_only(&param_server, StringCast<ANSICHAR>(*Parameter.Name).Get(), Parameter.ReadOnly);
    
    ParametersCache.Add(Parameter.Name, Parameter);
}

void UROS2ParameterSubsystem::DeleteParameter(const FString& ParameterName)
{
    rclc_delete_parameter(&param_server, StringCast<ANSICHAR>(*ParameterName).Get());
}

FROS2Parameter* UROS2ParameterSubsystem::UpdateParameterInternal(const Parameter& NewParam)
{
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

bool UROS2ParameterBlueprintLibrary::GetBooleanValue(const FROS2Parameter& Param)
{
    if (Param.Value.IsType<bool>())
    {
        return Param.Value.Get<bool>();
    }
    return false;
}

int64 UROS2ParameterBlueprintLibrary::GetIntegerValue(const FROS2Parameter& Param)
{
    if (Param.Value.IsType<int64>())
    {
        return Param.Value.Get<int64>();
    }
    return 0;
}

double UROS2ParameterBlueprintLibrary::GetDoubleValue(const FROS2Parameter& Param)
{
    if (Param.Value.IsType<double>())
    {
        return Param.Value.Get<double>();
    }
    return 0.0;
}

void UROS2ParameterBlueprintLibrary::SetBooleanValue(FROS2Parameter& Param, bool InValue)
{
    Param.Type = UParameterType::Boolean;
    Param.Value.Set<bool>(InValue);
}

void UROS2ParameterBlueprintLibrary::SetIntegerValue(FROS2Parameter& Param, int64 InValue, FROS2Parameter& OutValue)
{
    Param.Type = UParameterType::Integer;
    Param.Value.Set<int64>(InValue);
    OutValue = Param;
}

void UROS2ParameterBlueprintLibrary::SetDoubleValue(FROS2Parameter& Param, double InValue)
{
    Param.Type = UParameterType::Double;
    Param.Value.Set<double>(InValue);
}