// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from geometry_msgs/TwistWithCovariance.msg - do not modify

#pragma once

#include <CoreMinimal.h>

#include "Conversions.h"
#include "geometry_msgs/msg/twist_with_covariance.h"

#include "Msgs/ROS2GenericMsg.h"
#include "ROS2TwistMsg.h"

#include "ROS2TwistWithCovarianceMsg.generated.h"

USTRUCT(Blueprintable)
struct RCLUE_API FROSTwistWithCovariance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FROSTwist twist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> covariance = ArrayInitialisers::FloatArray(36); //double[36]
	
	void SetFromROS2(const geometry_msgs__msg__TwistWithCovariance& in_ros_data)
	{
		twist.SetFromROS2(in_ros_data.twist);
		covariance = ROS2MsgToUE::FromArray(in_ros_data.covariance);
	}

	void SetROS2(geometry_msgs__msg__TwistWithCovariance& out_ros_data) const
	{
    	twist.SetROS2(out_ros_data.twist);
		UEToROS2Msg::SetSequence(covariance, out_ros_data.covariance);
	}
};

UCLASS()
class RCLUE_API UROS2TwistWithCovarianceMsg : public UROS2GenericMsg
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Fini() override;

	virtual const rosidl_message_type_support_t* GetTypeSupport() const override;
	
  	UFUNCTION(BlueprintCallable)
	void SetMsg(const FROSTwistWithCovariance& Input);
	
  	UFUNCTION(BlueprintCallable)
	void GetMsg(FROSTwistWithCovariance& Output) const;
	
	virtual void* Get() override;

private:
	virtual FString MsgToString() const override;

	geometry_msgs__msg__TwistWithCovariance twist_with_covariance_msg;
};