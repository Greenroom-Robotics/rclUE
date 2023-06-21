// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.
#pragma once

#include <Components/ActorComponent.h>
#include <CoreMinimal.h>
#include <ROS2Node.h>

#include "ROS2Publisher.generated.h"


UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class RCLUE_API UROS2Publisher : public UActorComponent
{
    GENERATED_BODY()

public:
    UROS2Publisher(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition="!bQosOverride"))
    UROS2QoS QosProfilePreset = UROS2QoS::Default;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bQosOverride = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition="bQosOverride"))
    UROS2QosHistoryPolicy QosHistoryPolicy = UROS2QosHistoryPolicy::KEEP_LAST;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition="bQosOverride"))
    int32 QosDepth = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition="bQosOverride"))
    UROS2QosReliabilityPolicy QosReliabilityPolicy = UROS2QosReliabilityPolicy::RELIABLE;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition="bQosOverride"))
    UROS2QosDurabilityPolicy QosDurabilityPolicy = UROS2QosDurabilityPolicy::VOLATILE;

/*
    struct rmw_time_t 	deadline
        The period at which messages are expected to be sent/received. More...
    
    struct rmw_time_t 	lifespan
        The age at which messages are considered expired and no longer valid. More...
    
    enum rmw_qos_liveliness_policy_t 	liveliness
        Liveliness QoS policy setting. More...
    
    struct rmw_time_t 	liveliness_lease_duration
        The time within which the RMW node or publisher must show that it is alive. More...

*/

    void Init();
    
    UFUNCTION(BlueprintCallable)
    void UpdateAndPublishMessage();

    UFUNCTION()
    virtual void Destroy();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TopicName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
    bool bPublishOnTimer = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition="bPublishOnTimer"))
    float PublicationFrequencyHz = 10.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UROS2GenericMsg> TopicType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPublish = true;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    AROS2Node* ROSNode = nullptr;

    UPROPERTY(BlueprintReadOnly)
    UROS2State State = UROS2State::Created;

    // TODO refactor this class into two, split out ROS stuff from actorcomponent
    UPROPERTY(BlueprintReadOnly)
    UROS2GenericMsg* TopicMessage;

    UFUNCTION(BlueprintCallable)
    void PublishMsg(UROS2GenericMsg* Message, bool async=false);

protected:
    UFUNCTION(BlueprintNativeEvent)
    void UpdateMessage(UROS2GenericMsg* InMessage);

    void virtual UpdateMessage_Implementation(UROS2GenericMsg* InMessage)
    {
        checkNoEntry();
    }

    UFUNCTION(BlueprintCallable)
    void Publish();



    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FTimerHandle TimerHandle;

    FCriticalSection Mutex;
    
    const void* PublishedMsg = nullptr;

    rcl_publisher_t RclPublisher;

private:
    TFuture<void> AsyncPublisherFuture;
};
