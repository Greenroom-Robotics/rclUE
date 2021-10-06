// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from sensor_msgs/Range.msg - do not modify

#pragma once

#include <CoreMinimal.h>

#include "sensor_msgs/msg/range.h"

#include "Msgs/ROS2GenericMsg.h"
#include "rclcUtilities.h"

#include "ROS2RangeMsg.generated.h"

USTRUCT(Blueprintable)
struct RCLUE_API FROSRange
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int header_stamp_sec;

	unsigned int header_stamp_nanosec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString header_frame_id;

	uint8 radiation_type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float field_of_view;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float min_range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float max_range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float range;

	

	void SetFromROS2(const sensor_msgs__msg__Range& in_ros_data)
	{
    	header_stamp_sec = in_ros_data.header.stamp.sec;

		header_stamp_nanosec = in_ros_data.header.stamp.nanosec;

		header_frame_id.AppendChars(in_ros_data.header.frame_id.data, in_ros_data.header.frame_id.size);

		radiation_type = in_ros_data.radiation_type;

		field_of_view = in_ros_data.field_of_view;

		min_range = in_ros_data.min_range;

		max_range = in_ros_data.max_range;

		range = in_ros_data.range;

		
	}

	void SetROS2(sensor_msgs__msg__Range& out_ros_data) const
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

		out_ros_data.radiation_type = radiation_type;

		out_ros_data.field_of_view = field_of_view;

		out_ros_data.min_range = min_range;

		out_ros_data.max_range = max_range;

		out_ros_data.range = range;

		
	}
};

UCLASS()
class RCLUE_API UROS2RangeMsg : public UROS2GenericMsg
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Fini() override;

	virtual const rosidl_message_type_support_t* GetTypeSupport() const override;
	
  	UFUNCTION(BlueprintCallable)
	void SetMsg(const FROSRange& Input);
	
  	UFUNCTION(BlueprintCallable)
	void GetMsg(FROSRange& Output) const;
	
	virtual void* Get() override;

private:
	virtual FString MsgToString() const override;

	sensor_msgs__msg__Range range_msg;
};