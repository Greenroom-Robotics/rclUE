#pragma once

#include "ROS2Subsystem.h"
#include "ROS2Support.h"
#include "rclcUtilities.h"
#include "rclc_parameter/rclc_parameter.h"

#include <rcl_interfaces/rcl_interfaces/srv/set_parameters_atomically.h>

#include <CoreMinimal.h>
#include <Tickable.h>
#include <Misc/TVariant.h>

#include "ROS2ParameterSubsystem.generated.h"

UENUM(BlueprintType)
enum class UParameterType : uint8
{
  Boolean UMETA(DisplayName = "Boolean"),
  Integer UMETA(DisplayName = "Integer"),
  Double  UMETA(DisplayName = "Double")
};

inline const TMap<UParameterType, rclc_parameter_type_t> ParameterType_LUT = {
  { UParameterType::Boolean, RCLC_PARAMETER_BOOL },
  { UParameterType::Integer, RCLC_PARAMETER_INT },
  { UParameterType::Double, RCLC_PARAMETER_DOUBLE }
};

USTRUCT(Blueprintable)
struct RCLUE_API FROS2Parameter
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString Name;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UParameterType Type = UParameterType::Boolean;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString Description;

  TVariant<bool, int64, double> Value;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString AdditionalConstraints = "";

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  bool ReadOnly = false;
};

UCLASS()
class RCLUE_API UROS2ParameterBlueprintLibrary final : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintPure, Category = "ROS2|Parameters")
  static bool GetBooleanParameter(const FROS2Parameter& Param);

  UFUNCTION(BlueprintPure, Category = "ROS2|Parameters")
  static int64 GetIntegerParameter(const FROS2Parameter& Param);

  UFUNCTION(BlueprintPure, Category = "ROS2|Parameters")
  static double GetDoubleParameter(const FROS2Parameter& Param);

  UFUNCTION(BlueprintCallable, Category = "ROS2|Parameters")
  static FROS2Parameter& SetBooleanParameter(UPARAM(ref) FROS2Parameter& Param, bool InValue);

  UFUNCTION(BlueprintCallable, Category = "ROS2|Parameters")
  static FROS2Parameter& SetIntegerParameter(UPARAM(ref) FROS2Parameter& Param, int64 InValue);

  UFUNCTION(BlueprintCallable, Category = "ROS2|Parameters")
  static FROS2Parameter& SetDoubleParameter(UPARAM(ref) FROS2Parameter& Param, double InValue);
};

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FOnParameterAddedDelegate, UROS2ParameterSubsystem, OnParameterAdded,
                                                   FROS2Parameter, AddedParameter);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FOnParameterChangedDelegate, UROS2ParameterSubsystem,
                                                   OnParameterChanged, FROS2Parameter, ChangedParameter);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FOnParameterDeletedDelegate, UROS2ParameterSubsystem,
                                                   OnParameterDeleted, FString, DeletedParameterName);

UCLASS(Blueprintable)
class RCLUE_API UROS2ParameterSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
  GENERATED_BODY()

public:
  virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

  virtual void Initialize(FSubsystemCollectionBase& Collection) override;

  virtual void Deinitialize() override;

  virtual void Tick(float DeltaTime) override;

  virtual bool IsTickable() const override;

  virtual bool IsTickableWhenPaused() const override;

  virtual bool IsTickableInEditor() const override;

  virtual TStatId GetStatId() const override;

  UFUNCTION(BlueprintCallable)
  FROS2Parameter GetParameterByName(const FString& Name);

  UFUNCTION(BlueprintCallable)
  void AddParameter(const FROS2Parameter& Parameter);

  UFUNCTION(BlueprintCallable)
  void DeleteParameter(const FROS2Parameter& Parameter);

  UFUNCTION(BlueprintCallable)
  void DeleteParameterByName(const FString& ParameterName);

  UPROPERTY(BlueprintAssignable)
  FOnParameterAddedDelegate OnParameterAdded;

  UPROPERTY(BlueprintAssignable)
  FOnParameterChangedDelegate OnParameterChanged;

  UPROPERTY(BlueprintAssignable)
  FOnParameterDeletedDelegate OnParameterDeleted;

  FROS2Parameter* UpdateParameterInternal(const Parameter& NewParam);

  UFUNCTION(BlueprintCallable)
  void UpdateParameter(const FROS2Parameter& Param);

  friend void on_set_parameters_atomically(const void*, void*, void*);

protected:
  TMap<FString, FROS2Parameter> ParametersCache;
  FCriticalSection              Mutex;

  bool                    bIsInitialized = false;
  rclc_executor_t         executor;
  rclc_parameter_server_t param_server;

  rcl_interfaces__srv__SetParametersAtomically_Request            set_atomically_req;
  rcl_interfaces__srv__SetParametersAtomically_Response           set_atomically_res;
};
