// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.

#include "Msgs/ROS2StringMsg.h"

#include "Kismet/GameplayStatics.h"

void UROS2StringMsg::Init()
{
    example_interfaces__msg__String__init(&string_pub_msg);
}

void UROS2StringMsg::Fini()
{
    example_interfaces__msg__String__fini(&string_pub_msg);
}

const rosidl_message_type_support_t* UROS2StringMsg::GetTypeSupport() const
{
    return ROSIDL_GET_MSG_TYPE_SUPPORT(example_interfaces, msg, String);
}

void UROS2StringMsg::Update(const FString& stringData)
{
    const unsigned int StringMsgCapacity = stringData.Len() + 1;
    string_pub_msg.data.data = (char*)malloc(StringMsgCapacity);
    string_pub_msg.data.capacity = StringMsgCapacity;
    snprintf(string_pub_msg.data.data, string_pub_msg.data.capacity, "%s", TCHAR_TO_UTF8(*stringData));
    string_pub_msg.data.size = strlen(string_pub_msg.data.data);
}

void* UROS2StringMsg::Get()
{
    return &string_pub_msg;
}

FString UROS2StringMsg::MsgToString() const
{
    return FString(string_pub_msg.data.data);
}
