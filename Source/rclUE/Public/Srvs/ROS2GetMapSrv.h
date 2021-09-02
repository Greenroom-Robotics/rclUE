// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from nav_msgs/GetMap.srv - do not modify

#pragma once

#include <CoreMinimal.h>

#include "Srvs/ROS2GenericSrv.h"
#include "rclcUtilities.h"
#include "nav_msgs/srv/get_map.h"

#include "ROS2GetMapSrv.generated.h"

// potential problem: if this struct is defined multiple times!
USTRUCT(Blueprintable)
struct RCLUE_API FROSGetMap_Request
{
	GENERATED_BODY()

public:
	

	void SetFromROS2(const nav_msgs__srv__GetMap_Request& in_ros_data)
	{
    	
	}

	void SetROS2(nav_msgs__srv__GetMap_Request& out_ros_data) const
	{
    	
	}
};

USTRUCT(Blueprintable)
struct RCLUE_API FROSGetMap_Response
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int map_header_stamp_sec;

	unsigned int map_header_stamp_nanosec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString map_header_frame_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int map_info_map_load_time_sec;

	unsigned int map_info_map_load_time_nanosec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float map_info_resolution;

	unsigned int map_info_width;

	unsigned int map_info_height;

	double map_info_origin_position_x;

	double map_info_origin_position_y;

	double map_info_origin_position_z;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuat map_info_origin_orientation;

	TArray<int8> map_data;

	

	void SetFromROS2(const nav_msgs__srv__GetMap_Response& in_ros_data)
	{
    	map_header_stamp_sec = in_ros_data.map.header.stamp.sec;

		map_header_stamp_nanosec = in_ros_data.map.header.stamp.nanosec;

		map_header_frame_id.AppendChars(in_ros_data.map.header.frame_id.data, in_ros_data.map.header.frame_id.size);

		map_info_map_load_time_sec = in_ros_data.map.info.map_load_time.sec;

		map_info_map_load_time_nanosec = in_ros_data.map.info.map_load_time.nanosec;

		map_info_resolution = in_ros_data.map.info.resolution;

		map_info_width = in_ros_data.map.info.width;

		map_info_height = in_ros_data.map.info.height;

		map_info_origin_position_x = in_ros_data.map.info.origin.position.x;

		map_info_origin_position_y = in_ros_data.map.info.origin.position.y;

		map_info_origin_position_z = in_ros_data.map.info.origin.position.z;

		map_info_origin_orientation.X = in_ros_data.map.info.origin.orientation.x;
		map_info_origin_orientation.Y = in_ros_data.map.info.origin.orientation.y;
		map_info_origin_orientation.Z = in_ros_data.map.info.origin.orientation.z;
		map_info_origin_orientation.W = in_ros_data.map.info.origin.orientation.w;

		for (int i = 0; i < in_ros_data.map.data.size; i++)
		{
			map_data[i] = in_ros_data.map.data.data[i];
		}

		
	}

	void SetROS2(nav_msgs__srv__GetMap_Response& out_ros_data) const
	{
    	out_ros_data.map.header.stamp.sec = map_header_stamp_sec;

		out_ros_data.map.header.stamp.nanosec = map_header_stamp_nanosec;

		if (out_ros_data.map.header.frame_id.data != nullptr)
		{
			free(out_ros_data.map.header.frame_id.data);
		}
		out_ros_data.map.header.frame_id.data = (decltype(out_ros_data.map.header.frame_id.data))malloc((map_header_frame_id.Len() + 1)*sizeof(decltype(*out_ros_data.map.header.frame_id.data)));
		memcpy(out_ros_data.map.header.frame_id.data, TCHAR_TO_UTF8(*map_header_frame_id), (map_header_frame_id.Len()+1)*sizeof(char));
		out_ros_data.map.header.frame_id.size = map_header_frame_id.Len();
		out_ros_data.map.header.frame_id.capacity = map_header_frame_id.Len() + 1;

		out_ros_data.map.info.map_load_time.sec = map_info_map_load_time_sec;

		out_ros_data.map.info.map_load_time.nanosec = map_info_map_load_time_nanosec;

		out_ros_data.map.info.resolution = map_info_resolution;

		out_ros_data.map.info.width = map_info_width;

		out_ros_data.map.info.height = map_info_height;

		out_ros_data.map.info.origin.position.x = map_info_origin_position_x;

		out_ros_data.map.info.origin.position.y = map_info_origin_position_y;

		out_ros_data.map.info.origin.position.z = map_info_origin_position_z;

		out_ros_data.map.info.origin.orientation.x = map_info_origin_orientation.X;
		out_ros_data.map.info.origin.orientation.y = map_info_origin_orientation.Y;
		out_ros_data.map.info.origin.orientation.z = map_info_origin_orientation.Z;
		out_ros_data.map.info.origin.orientation.w = map_info_origin_orientation.W;

		if (out_ros_data.map.data.data != nullptr)
		{
			free(out_ros_data.map.data.data);
		}
		out_ros_data.map.data.data = (decltype(out_ros_data.map.data.data))malloc((map_data.Num())*sizeof(decltype(*out_ros_data.map.data.data)));
		
		for (int i = 0; i < map_data.Num(); i++)
		{
			out_ros_data.map.data.data[i] = map_data[i];
		}

		out_ros_data.map.data.size = map_data.Num();
		out_ros_data.map.data.capacity = map_data.Num();

		
	}
};

UCLASS()
class RCLUE_API UROS2GetMapSrv : public UROS2GenericSrv
{
	GENERATED_BODY()

public:
  	UFUNCTION(BlueprintCallable)
	virtual void Init() override;

  	UFUNCTION(BlueprintCallable)
	virtual void Fini() override;

	virtual const rosidl_service_type_support_t* GetTypeSupport() const override;
	
	// used by client
  	UFUNCTION(BlueprintCallable)
	void SetRequest(const FROSGetMap_Request& Request);
	
	// used by service
  	UFUNCTION(BlueprintCallable)
	void GetRequest(FROSGetMap_Request& Request) const;
	
	// used by service
  	UFUNCTION(BlueprintCallable)
	void SetResponse(const FROSGetMap_Response& Response);
	
	// used by client
  	UFUNCTION(BlueprintCallable)
	void GetResponse(FROSGetMap_Response& Response) const;
	
	virtual void* GetRequest() override;
	virtual void* GetResponse() override;

private:
	virtual FString SrvRequestToString() const override;
	virtual FString SrvResponseToString() const override;

	nav_msgs__srv__GetMap_Request GetMap_req;
	nav_msgs__srv__GetMap_Response GetMap_res;
};