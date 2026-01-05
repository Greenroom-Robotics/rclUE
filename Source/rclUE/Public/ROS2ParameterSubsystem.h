#pragma once

#include "ROS2Subsystem.h"
#include "ROS2Support.h"
#include "rclcUtilities.h"
#include "rclc_parameter/rclc_parameter.h"

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <Tickable.h>
#include <Misc/TVariant.h>

#include "ROS2ParameterSubsystem.generated.h"

UENUM()
enum class UParameterType
{
    Boolean,
    Integer,
    Double
};

static const TMap<UParameterType, rclc_parameter_type_t> ParameterType_LUT = {
    {UParameterType::Boolean, RCLC_PARAMETER_BOOL},
    {UParameterType::Integer, RCLC_PARAMETER_INT},
    {UParameterType::Double, RCLC_PARAMETER_DOUBLE}
};

USTRUCT(Blueprintable)
struct RCLUE_API FROS2Parameter
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UParameterType Type;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;
    
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TVariant<bool, int64, double> Value;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString AdditionalConstraints = "";
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool ReadOnly = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnParameterAddedDelegate, FROS2Parameter&, AddedParameter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnParameterChangedDelegate, FROS2Parameter&, ChangedParameter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnParameterDeletedDelegate, FString, DeletedParameterName);


UCLASS(Blueprintable)
class RCLUE_API UROS2ParameterSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
    GENERATED_BODY()

public:
    // UFUNCTION(BlueprintCallable, Category = "ROS2")
    // UROS2Support* GetSupport() const;

    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    virtual void Deinitialize() override;

    virtual void Tick(float DeltaTime) override;
    
    virtual bool IsTickable() const override;
    
    virtual bool IsTickableWhenPaused() const override;
    
    virtual bool IsTickableInEditor() const override;
    
    virtual TStatId GetStatId() const override;

    // UPROPERTY(BlueprintAssignable)
    // FOnNodeInitialisedDelegate OnNodeInitialised;
    
    UFUNCTION(BlueprintCallable)
    void AddParameter(const FROS2Parameter& Parameter);
    
    UFUNCTION(BlueprintCallable)
    void DeleteParameter(const FString& ParameterName);

    UPROPERTY(BlueprintAssignable)
    FOnParameterAddedDelegate OnParameterAdded;

    UPROPERTY(BlueprintAssignable)
    FOnParameterChangedDelegate OnParameterChanged;

    UPROPERTY(BlueprintAssignable)
    FOnParameterDeletedDelegate OnParameterDeleted;

    FROS2Parameter* UpdateParameterInternal(const Parameter& NewParam);

protected:
    UPROPERTY()
    FTimerHandle TimerHandle;
    
    TMap<FString, FROS2Parameter> ParametersCache;
    
    
    rclc_executor_t executor;
    rclc_parameter_server_t param_server;
};
