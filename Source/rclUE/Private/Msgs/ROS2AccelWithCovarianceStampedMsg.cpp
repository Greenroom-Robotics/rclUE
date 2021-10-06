// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from geometry_msgs/AccelWithCovarianceStamped.msg - do not modify

#include "Msgs/ROS2AccelWithCovarianceStampedMsg.h"

#include "Kismet/GameplayStatics.h"

void UROS2AccelWithCovarianceStampedMsg::Init()
{
	geometry_msgs__msg__AccelWithCovarianceStamped__init(&accel_with_covariance_stamped_msg);
}

void UROS2AccelWithCovarianceStampedMsg::Fini()
{
	geometry_msgs__msg__AccelWithCovarianceStamped__fini(&accel_with_covariance_stamped_msg);
}

const rosidl_message_type_support_t* UROS2AccelWithCovarianceStampedMsg::GetTypeSupport() const
{
	return ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, AccelWithCovarianceStamped);
}

void UROS2AccelWithCovarianceStampedMsg::SetMsg(const FROSAccelWithCovarianceStamped& Inputs)
{
    Inputs.SetROS2(accel_with_covariance_stamped_msg);
}

void UROS2AccelWithCovarianceStampedMsg::GetMsg(FROSAccelWithCovarianceStamped& Outputs) const
{
    Outputs.SetFromROS2(accel_with_covariance_stamped_msg);
}

void* UROS2AccelWithCovarianceStampedMsg::Get()
{
	return &accel_with_covariance_stamped_msg;
}

FString UROS2AccelWithCovarianceStampedMsg::MsgToString() const
{
    /* TODO: Fill here */
	checkNoEntry();
	return FString();
}