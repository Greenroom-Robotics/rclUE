#pragma once

#include <Components/ActorComponent.h>
#include <CoreMinimal.h>
#include <ROS2Node.h>

#include "ROS2Subscriber.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingMessageDelegate, UROS2GenericMsg*, IncomingMessage);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class RCLUE_API UROS2Subscriber : public UActorComponent
{
    GENERATED_BODY()

public:
    UROS2Subscriber(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition="!bQosOverride"))
    UROS2QoS QosProfilePreset = UROS2QoS::Default;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bQosOverride = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition="bQosOverride"))
    FROS2QualityOfService Qos;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TopicName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UROS2GenericMsg> TopicType;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    AROS2Node* ROSNode = nullptr;

    UPROPERTY(BlueprintReadOnly)
    UROS2State State = UROS2State::Created;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAutoInitialise = false;

    UPROPERTY(BlueprintReadOnly)
    UROS2GenericMsg* TopicMessage;

    rcl_subscription_t rcl_subscription;

    UPROPERTY(BlueprintReadWrite)
    FIncomingMessageDelegate IncomingMessageDelegate;

    UFUNCTION(BlueprintCallable)
    void Init();

    bool FindAndSetROSNode();
    void WhenNodeInits();
    void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    void HandleMessage(UROS2GenericMsg* Message);

    UFUNCTION()
    virtual void Destroy();

    UFUNCTION(BlueprintCallable)
    void Reinitialise();

    UFUNCTION(BlueprintNativeEvent)
    void IncomingMessage(UROS2GenericMsg* Message);

protected:
    virtual void IncomingMessage_Implementation(UROS2GenericMsg* Message);
};
