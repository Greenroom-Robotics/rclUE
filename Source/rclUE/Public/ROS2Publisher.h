// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.

// Class implementing ROS2 publishers
// Message type is defined by MsgClass

#pragma once

#include <Components/ActorComponent.h>
#include <CoreMinimal.h>
#include <ROS2Node.h>

#include "ROS2Publisher.generated.h"

// BP requires a custom-made callback thus it must be Dynamic
DECLARE_DYNAMIC_DELEGATE_OneParam(FPublisherUpdateCallback, UROS2GenericMsg*, InTopicMessage);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class RCLUE_API UROS2Publisher : public UActorComponent
{
    GENERATED_BODY()

public:
    UROS2Publisher();

    virtual void InitializeWithROS2(AROS2Node* InROS2Node)
    {
        RegisterToROS2Node(InROS2Node);
    }
    UFUNCTION()
    void RegisterToROS2Node(AROS2Node* InROS2Node);

    UFUNCTION(BlueprintCallable)
    void Init();

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

    UFUNCTION(BlueprintCallable)
    void InitializeMessage();

    UFUNCTION(BlueprintCallable)
    void UpdateAndPublishMessage();

    UFUNCTION()
    virtual void Destroy();

    // this information is redundant with Topic, but it's needed to initialize it
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TopicName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPublishOnTimer = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition="bPublishOnTimer"))
    float PublicationFrequencyHz = 10.0;

    // this information is redundant with Topic, but it's needed to initialize it
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UROS2GenericMsg> MsgClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FPublisherUpdateCallback UpdateDelegate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPublish = true;

    UFUNCTION(BlueprintCallable)
    void SetupUpdateCallback()
    {
        UpdateDelegate.BindDynamic(this, &UROS2Publisher::UpdateMessage);
    }

    UFUNCTION(BlueprintCallable)
    virtual void RevokeUpdateCallback()
    {
        UpdateDelegate.Unbind();
    }

    UFUNCTION()
    virtual void UpdateMessage(UROS2GenericMsg* InMessage)
    {
        checkNoEntry();
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AROS2Node* OwnerNode = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UROS2State State = UROS2State::Created;

protected:
    UFUNCTION(BlueprintCallable)
    void Publish();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UROS2GenericMsg* TopicMessage;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FTimerHandle TimerHandle;

    const void* PublishedMsg = nullptr;

    rcl_publisher_t RclPublisher;
};
