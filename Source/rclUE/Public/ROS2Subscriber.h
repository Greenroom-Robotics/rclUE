#pragma once

#include <Components/ActorComponent.h>
#include <CoreMinimal.h>
#include "rclcUtilities.h"

#include "ROS2Subscriber.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingMessageDelegate, UROS2GenericMsg*, IncomingMessage);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FSubscriberMessageReceivedSignature, UROS2Subscriber,
                                                   OnMessageReceived, UROS2GenericMsg*, IncomingMessage);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class RCLUE_API UROS2Subscriber : public UActorComponent
{
  GENERATED_BODY()

public:
  UROS2Subscriber(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "!bQosOverride", ExposeOnSpawn = true))
  UROS2QoS QosProfilePreset = UROS2QoS::Default;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
  bool bQosOverride = false;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bQosOverride", ExposeOnSpawn = true))
  FROS2QualityOfService Qos;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
  FString TopicName;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
  TSubclassOf<UROS2GenericMsg> TopicType;

  UPROPERTY(BlueprintReadOnly)
  UROS2State State = UROS2State::Created;

  UPROPERTY(BlueprintReadOnly)
  UROS2GenericMsg* TopicMessage;

  UPROPERTY(BlueprintReadWrite)
  FIncomingMessageDelegate IncomingMessageDelegate;

  UPROPERTY(BlueprintAssignable)
  FSubscriberMessageReceivedSignature OnMessageReceived;

  virtual void BeginPlay() override;
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  void HandleMessage(UROS2GenericMsg* Message);

  UFUNCTION(BlueprintCallable)
  void Reinitialise();

  UFUNCTION(BlueprintNativeEvent)
  void IncomingMessage(UROS2GenericMsg* Message);

  // TODO: this struct is accessed externally, which maybe it shouldn't be
  rcl_subscription_t rcl_subscription;

protected:
  virtual void IncomingMessage_Implementation(UROS2GenericMsg* Message);

  void Init();
  void Destroy();
};
