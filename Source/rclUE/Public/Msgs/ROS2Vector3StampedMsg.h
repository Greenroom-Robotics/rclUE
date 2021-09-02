// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from geometry_msgs/Vector3Stamped.msg - do not modify

#pragma once

#include <CoreMinimal.h>

#include "geometry_msgs/msg/vector3_stamped.h"

#include "Msgs/ROS2GenericMsg.h"
#include "rclcUtilities.h"

#include "ROS2Vector3StampedMsg.generated.h"

USTRUCT(Blueprintable)
struct RCLUE_API FROSVector3Stamped
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int header_stamp_sec;

	unsigned int header_stamp_nanosec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString header_frame_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector vector;

	

	void SetFromROS2(const geometry_msgs__msg__Vector3Stamped& in_ros_data)
	{
    	header_stamp_sec = in_ros_data.header.stamp.sec;

		header_stamp_nanosec = in_ros_data.header.stamp.nanosec;

		header_frame_id.AppendChars(in_ros_data.header.frame_id.data, in_ros_data.header.frame_id.size);

		vector.X = in_ros_data.vector.x;
		vector.Y = in_ros_data.vector.y;
		vector.Z = in_ros_data.vector.z;

		
	}

	void SetROS2(geometry_msgs__msg__Vector3Stamped& out_ros_data) const
	{
    	out_ros_data.header.stamp.sec = header_stamp_sec;

		out_ros_data.header.stamp.nanosec = header_stamp_nanosec;

		if (out_ros_data.header.frame_id.data != nullptr)
		{
			free(out_ros_data.header.frame_id.data);
		}
		out_ros_data.header.frame_id.data = (decltype(out_ros_data.header.frame_id.data))malloc((header_frame_id.Len() + 1)*sizeof(decltype(*out_ros_data.header.frame_id.data)));
		memcpy(out_ros_data.header.frame_id.data, TCHAR_TO_UTF8(*header_frame_id), (header_frame_id.Len()+1)*sizeof(char));
		out_ros_data.header.frame_id.size = header_frame_id.Len();
		out_ros_data.header.frame_id.capacity = header_frame_id.Len() + 1;

		out_ros_data.vector.x = vector.X;
		out_ros_data.vector.y = vector.Y;
		out_ros_data.vector.z = vector.Z;

		
	}
};

UCLASS()
class RCLUE_API UROS2Vector3StampedMsg : public UROS2GenericMsg
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Fini() override;

	virtual const rosidl_message_type_support_t* GetTypeSupport() const override;
	
  	UFUNCTION(BlueprintCallable)
	void SetMsg(const FROSVector3Stamped& Input);
	
  	UFUNCTION(BlueprintCallable)
	void GetMsg(FROSVector3Stamped& Output) const;
	
	virtual void* Get() override;

private:
	virtual FString MsgToString() const override;

	geometry_msgs__msg__Vector3Stamped vector3_stamped_msg;
};