// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from geometry_msgs/PoseArray.msg - do not modify

#pragma once

#include <CoreMinimal.h>

#include "geometry_msgs/msg/pose_array.h"

#include "Msgs/ROS2GenericMsg.h"
#include "rclcUtilities.h"

#include "ROS2PoseArrayMsg.generated.h"

USTRUCT(Blueprintable)
struct RCLUE_API FROSPoseArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int header_stamp_sec;

	unsigned int header_stamp_nanosec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString header_frame_id;

	TArray<double> poses_position_x;

	TArray<double> poses_position_y;

	TArray<double> poses_position_z;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuat> poses_orientation;

	

	void SetFromROS2(const geometry_msgs__msg__PoseArray& in_ros_data)
	{
    	header_stamp_sec = in_ros_data.header.stamp.sec;

		header_stamp_nanosec = in_ros_data.header.stamp.nanosec;

		header_frame_id.AppendChars(in_ros_data.header.frame_id.data, in_ros_data.header.frame_id.size);

		for (int i = 0; i < in_ros_data.poses.size; i++)
		{
			poses_position_x.Add(in_ros_data.poses.data[i].position.x);
		}

		for (int i = 0; i < in_ros_data.poses.size; i++)
		{
			poses_position_y.Add(in_ros_data.poses.data[i].position.y);
		}

		for (int i = 0; i < in_ros_data.poses.size; i++)
		{
			poses_position_z.Add(in_ros_data.poses.data[i].position.z);
		}

		for (int i = 0; i < in_ros_data.poses.size; i++)
		{
			poses_orientation.Add(FQuat());
			poses_orientation[i].X = in_ros_data.poses.data[i].orientation.x;
			poses_orientation[i].Y = in_ros_data.poses.data[i].orientation.y;
			poses_orientation[i].Z = in_ros_data.poses.data[i].orientation.z;
			poses_orientation[i].W = in_ros_data.poses.data[i].orientation.w;
		}

		
	}

	void SetROS2(geometry_msgs__msg__PoseArray& out_ros_data) const
	{
    	out_ros_data.header.stamp.sec = header_stamp_sec;

		out_ros_data.header.stamp.nanosec = header_stamp_nanosec;

		{
			FTCHARToUTF8 strUtf8( *header_frame_id );
			int32 strLength = strUtf8.Length();
			if (out_ros_data.header.frame_id.data != nullptr)
		{
			free(out_ros_data.header.frame_id.data);
		}
		out_ros_data.header.frame_id.data = (decltype(out_ros_data.header.frame_id.data))malloc((strLength+1)*sizeof(decltype(*out_ros_data.header.frame_id.data)));
		memcpy(out_ros_data.header.frame_id.data, TCHAR_TO_UTF8(*header_frame_id), (strLength+1)*sizeof(char));
			out_ros_data.header.frame_id.size = strLength;
			out_ros_data.header.frame_id.capacity = strLength + 1;
		}

		if (out_ros_data.poses.data != nullptr)
		{
			free(out_ros_data.poses.data);
		}
		out_ros_data.poses.data = (decltype(out_ros_data.poses.data))malloc(poses_position_x.Num() * (sizeof(poses_position_x) + sizeof(poses_position_y) + sizeof(poses_position_z) + sizeof(poses_orientation)));
		out_ros_data.poses.size = poses_position_x.Num();
		out_ros_data.poses.capacity = poses_position_x.Num();
		for (int i = 0; i < poses_position_x.Num(); i++)
		{
			out_ros_data.poses.data[i].position.x = poses_position_x[i];

			out_ros_data.poses.data[i].position.y = poses_position_y[i];

			out_ros_data.poses.data[i].position.z = poses_position_z[i];

			out_ros_data.poses.data[i].orientation.x = poses_orientation[i].X;
			out_ros_data.poses.data[i].orientation.y = poses_orientation[i].Y;
			out_ros_data.poses.data[i].orientation.z = poses_orientation[i].Z;
			out_ros_data.poses.data[i].orientation.w = poses_orientation[i].W;

			}
	
	}
};

UCLASS()
class RCLUE_API UROS2PoseArrayMsg : public UROS2GenericMsg
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Fini() override;

	virtual const rosidl_message_type_support_t* GetTypeSupport() const override;
	
  	UFUNCTION(BlueprintCallable)
	void SetMsg(const FROSPoseArray& Input);
	
  	UFUNCTION(BlueprintCallable)
	void GetMsg(FROSPoseArray& Output) const;
	
	virtual void* Get() override;

private:
	virtual FString MsgToString() const override;

	geometry_msgs__msg__PoseArray pose_array_msg;
};