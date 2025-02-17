// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.

// Class implementing ROS2 service clients
// Service type is defined by SrvClass

#pragma once

// UE
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

// rclUE
#include "ROS2GenericMsg.h"
#include "ROS2Node.h"
#include "ROS2GenericSrv.h"

#include "ROS2ServiceClient.generated.h"

DECLARE_DELEGATE_OneParam(FServiceClientCallback, UROS2GenericSrv* /*Service*/);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RCLUE_API UROS2ServiceClient : public UActorComponent
{
    GENERATED_BODY()

public:
    UROS2ServiceClient();

public:
    UFUNCTION(BlueprintCallable)
    void Init(UROS2QoS QoS);

    UFUNCTION(BlueprintCallable)
    void InitializeService();

    UFUNCTION(BlueprintCallable)
    void UpdateAndSendRequest();

    UFUNCTION()
    virtual void Destroy();

    // this information is redundant with Topic, but it's used to initialize it
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ServiceName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UROS2GenericSrv> SrvClass;

    // used to pass data for the request
    FServiceClientCallback RequestDelegate;

    // used to receive the answer
    FServiceClientCallback AnswerDelegate;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    AROS2Node* ROSNode;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UROS2State State = UROS2State::Created;

    rcl_client_t client;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UROS2GenericSrv* Service;

    bool Ready;

protected:
    UFUNCTION()
    void SendRequest();

    const void* req;
    const void* res;
};
