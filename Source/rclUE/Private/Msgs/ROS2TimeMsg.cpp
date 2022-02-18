#include "Msgs/ROS2TimeMsg.h"

#include "Kismet/GameplayStatics.h"

void UROS2TimeMsg::Init()
{
    builtin_interfaces__msg__Time__init(&time_msg);
}

void UROS2TimeMsg::Fini()
{
    builtin_interfaces__msg__Time__fini(&time_msg);
}

const rosidl_message_type_support_t* UROS2TimeMsg::GetTypeSupport() const
{
    return ROSIDL_GET_MSG_TYPE_SUPPORT(builtin_interfaces, msg, Time);
}

void UROS2TimeMsg::SetMsg(const FROSTime& Inputs)
{
    Inputs.SetROS2(time_msg);
}

void UROS2TimeMsg::GetMsg(FROSTime& Outputs) const
{
    Outputs.SetFromROS2(time_msg);
}

void* UROS2TimeMsg::Get()
{
    return &time_msg;
}

FString UROS2TimeMsg::MsgToString() const
{
    /* TODO: Fill here */
    checkNoEntry();
    return FString();
}