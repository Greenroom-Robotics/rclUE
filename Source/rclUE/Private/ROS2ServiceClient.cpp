// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.

#include "ROS2ServiceClient.h"

DEFINE_LOG_CATEGORY(LogROS2Service);

// Sets default values for this component's properties
UROS2ServiceClient::UROS2ServiceClient()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UROS2ServiceClient::Init(UROS2QoS QoS)
{
    check(ROSNode != nullptr);
    check(ROSNode->State == UROS2State::Initialized);
    if (State == UROS2State::Created)
    {
        InitializeService();

        check(IsValid(Service));

        const rosidl_service_type_support_t* srv_type_support = Service->GetTypeSupport();

        client = rcl_get_zero_initialized_client();
        rcl_client_options_t client_opt = rcl_client_get_default_options();

        client_opt.qos = QoSProfiles_LUT[QoS];

        RCSOFTCHECK(rcl_client_init(&client, ROSNode->GetRCLNode(), srv_type_support, TCHAR_TO_UTF8(*ServiceName), &client_opt));

        State = UROS2State::Initialized;
    }

    Ready = false;
}

void UROS2ServiceClient::InitializeService()
{
    check(ServiceName != FString());
    check(SrvClass);

    Service = NewObject<UROS2GenericSrv>(this, SrvClass);

    check(IsValid(Service));

    Service->Init();
}

void UROS2ServiceClient::Destroy()
{
    if (Service != nullptr)
    {
        Service->Fini();
    }

    if (ROSNode != nullptr)
    {
        UE_LOG(LogROS2Service, Log, TEXT("Client Destroy - rcl_client_fini (%s)"), *__LOG_INFO__);
        RCSOFTCHECK(rcl_client_fini(&client, ROSNode->GetRCLNode()));
    }
}

void UROS2ServiceClient::UpdateAndSendRequest()
{
    UE_LOG(LogROS2Service, Log, TEXT("%s"), *__LOG_INFO__);
    check(State == UROS2State::Initialized);
    check(IsValid(ROSNode));

    RequestDelegate.ExecuteIfBound(Service);
    SendRequest();
}

void UROS2ServiceClient::SendRequest()
{
    UE_LOG(LogROS2Service, Log, TEXT("%s"), *__LOG_INFO__);
    check(State == UROS2State::Initialized);
    check(ROSNode != nullptr);

    req = Service->GetRequest();

    int64_t Seq;
    RCSOFTCHECK(rcl_send_request(&client, req, &Seq));
}