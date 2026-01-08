// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.
#pragma once

#include <Components/ActorComponent.h>
#include <CoreMinimal.h>

#include "rclcUtilities.h"

#include "ROS2Publisher.generated.h"


UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class RCLUE_API UROS2Publisher : public UActorComponent
{
    GENERATED_BODY()

public:
    UROS2Publisher(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition="!bQosOverride", ExposeOnSpawn = true))
    UROS2QoS QosProfilePreset = UROS2QoS::Default;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
    bool bQosOverride = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition="bQosOverride", ExposeOnSpawn = true))
    FROS2QualityOfService Qos;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
    FString TopicName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (InlineEditConditionToggle))
    bool bPublishOnTimer = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition="bPublishOnTimer"))
    float PublicationFrequencyHz = 10.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
    TSubclassOf<UROS2GenericMsg> TopicType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPublish = true;

    UPROPERTY(BlueprintReadOnly)
    UROS2State State = UROS2State::Created;

    // TODO refactor this class into two, split out ROS stuff from actorcomponent
    UPROPERTY(BlueprintReadOnly)
    UROS2GenericMsg* TopicMessage;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FTimerHandle TimerHandle;

    UFUNCTION(BlueprintCallable)
    void Reinitialise();

    void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION(BlueprintCallable)
    void UpdateAndPublishMessage();

    UFUNCTION(BlueprintCallable)
    virtual void Destroy();

    UFUNCTION(BlueprintCallable)
    void PublishMsg(UROS2GenericMsg* Message, bool async=false);

    UFUNCTION(BlueprintCallable)
    void Publish();

protected:
    UFUNCTION(BlueprintNativeEvent)
    void UpdateMessage(UROS2GenericMsg* InMessage);

    void virtual UpdateMessage_Implementation(UROS2GenericMsg* InMessage)
    {
        checkNoEntry();
    }

private:
    rcl_publisher_t RclPublisher;
    FCriticalSection Mutex;
    const void* PublishedMsg = nullptr;
    
    void Init();
    
    TFuture<void> AsyncPublisherFuture;
};
