// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from sensor_msgs/MultiEchoLaserScan.msg - do not modify

#pragma once

#include <CoreMinimal.h>

#include "sensor_msgs/msg/multi_echo_laser_scan.h"

#include "Msgs/ROS2GenericMsg.h"
#include "rclcUtilities.h"

#include "ROS2MultiEchoLaserScanMsg.generated.h"

USTRUCT(Blueprintable)
struct RCLUE_API FROSMultiEchoLaserScan
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int header_stamp_sec;

	unsigned int header_stamp_nanosec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString header_frame_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float angle_min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float angle_max;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float angle_increment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float time_increment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float scan_time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float range_min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float range_max;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> ranges_echoes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> intensities_echoes;

	

	void SetFromROS2(const sensor_msgs__msg__MultiEchoLaserScan& in_ros_data)
	{
    	header_stamp_sec = in_ros_data.header.stamp.sec;

		header_stamp_nanosec = in_ros_data.header.stamp.nanosec;

		header_frame_id.AppendChars(in_ros_data.header.frame_id.data, in_ros_data.header.frame_id.size);

		angle_min = in_ros_data.angle_min;

		angle_max = in_ros_data.angle_max;

		angle_increment = in_ros_data.angle_increment;

		time_increment = in_ros_data.time_increment;

		scan_time = in_ros_data.scan_time;

		range_min = in_ros_data.range_min;

		range_max = in_ros_data.range_max;

		for (int i = 0; i < in_ros_data.ranges.size; i++)
		{
			ranges_echoes[i] = in_ros_data.ranges.data[i].echoes.data[i];
		}

		for (int i = 0; i < in_ros_data.intensities.size; i++)
		{
			intensities_echoes[i] = in_ros_data.intensities.data[i].echoes.data[i];
		}

		
	}

	void SetROS2(sensor_msgs__msg__MultiEchoLaserScan& out_ros_data) const
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

		out_ros_data.angle_min = angle_min;

		out_ros_data.angle_max = angle_max;

		out_ros_data.angle_increment = angle_increment;

		out_ros_data.time_increment = time_increment;

		out_ros_data.scan_time = scan_time;

		out_ros_data.range_min = range_min;

		out_ros_data.range_max = range_max;

		if (out_ros_data.ranges.data != nullptr)
		{
			free(out_ros_data.ranges.data);
		}
		out_ros_data.ranges.data = (decltype(out_ros_data.ranges.data))malloc((ranges_echoes.Num())*sizeof(decltype(*out_ros_data.ranges.data)));
		
		for (int i = 0; i < ranges_echoes.Num(); i++)
		{
			out_ros_data.ranges.data[i].echoes.data[i] = ranges_echoes[i];
		}

		out_ros_data.ranges.size = ranges_echoes.Num();
		out_ros_data.ranges.capacity = ranges_echoes.Num();

		if (out_ros_data.intensities.data != nullptr)
		{
			free(out_ros_data.intensities.data);
		}
		out_ros_data.intensities.data = (decltype(out_ros_data.intensities.data))malloc((intensities_echoes.Num())*sizeof(decltype(*out_ros_data.intensities.data)));
		
		for (int i = 0; i < intensities_echoes.Num(); i++)
		{
			out_ros_data.intensities.data[i].echoes.data[i] = intensities_echoes[i];
		}

		out_ros_data.intensities.size = intensities_echoes.Num();
		out_ros_data.intensities.capacity = intensities_echoes.Num();

		
	}
};

UCLASS()
class RCLUE_API UROS2MultiEchoLaserScanMsg : public UROS2GenericMsg
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Fini() override;

	virtual const rosidl_message_type_support_t* GetTypeSupport() const override;
	
  	UFUNCTION(BlueprintCallable)
	void SetMsg(const FROSMultiEchoLaserScan& Input);
	
  	UFUNCTION(BlueprintCallable)
	void GetMsg(FROSMultiEchoLaserScan& Output) const;
	
	virtual void* Get() override;

private:
	virtual FString MsgToString() const override;

	sensor_msgs__msg__MultiEchoLaserScan multi_echo_laser_scan_msg;
};