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
    FROS2QualityOfService Qos;

    void Init();
    void WhenNodeInits();
    void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


    UFUNCTION(BlueprintCallable)
    void UpdateAndPublishMessage();

    UFUNCTION()
    virtual void Destroy();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TopicName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (InlineEditConditionToggle))
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAutoInitialise = false;

    // TODO refactor this class into two, split out ROS stuff from actorcomponent
    UPROPERTY(BlueprintReadOnly)
    UROS2GenericMsg* TopicMessage;

    UFUNCTION(BlueprintCallable)
    void PublishMsg(UROS2GenericMsg* Message, bool async=false);

    UFUNCTION(BlueprintCallable)
    void Publish();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FTimerHandle TimerHandle;

    FCriticalSection Mutex;
    
    const void* PublishedMsg = nullptr;

    rcl_publisher_t RclPublisher;

protected:
    UFUNCTION(BlueprintNativeEvent)
    void UpdateMessage(UROS2GenericMsg* InMessage);

    void virtual UpdateMessage_Implementation(UROS2GenericMsg* InMessage)
    {
        checkNoEntry();
    }

private:
    TFuture<void> AsyncPublisherFuture;
};
