#pragma once

#include <CoreMinimal.h>
#include "Conversions.h"
#include "ROS2GenericMsg.h"

#include "geographic_msgs/msg/geo_pose_with_covariance_stamped.h"


// Include directives for member types
#include "Msgs/ROS2Header.h"
#include "Msgs/ROS2GeoPoseWithCovariance.h"

#include "ROS2GeoPoseWithCovarianceStamped.generated.h"


USTRUCT(Blueprintable)
struct RCLUE_API FROSGeoPoseWithCovarianceStamped
{
    GENERATED_BODY()

    using ros_msg_c_typename = geographic_msgs__msg__GeoPoseWithCovarianceStamped;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FROSHeader header;
    // rclc type: std_msgs__msg__Header header

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FROSGeoPoseWithCovariance pose;
    // rclc type: geographic_msgs__msg__GeoPoseWithCovariance pose

    void SetFromROS2(const ros_msg_c_typename& in_ros_data)
    {
        header.SetFromROS2(in_ros_data.header);
        pose.SetFromROS2(in_ros_data.pose);
    }

    void SetROS2(ros_msg_c_typename& out_ros_data) const
    {
        header.SetROS2(out_ros_data.header);
        pose.SetROS2(out_ros_data.pose);
    }
};

UCLASS()
class RCLUE_API UROS2GeoPoseWithCovarianceStamped : public UROS2GenericMsg
{
    GENERATED_BODY()

    using ros_msg_c_typename = geographic_msgs__msg__GeoPoseWithCovarianceStamped;

public:
    virtual void Init() override
    {
        geographic_msgs__msg__GeoPoseWithCovarianceStamped__init(&geo_pose_with_covariance_stamped_msg);
    }

    virtual void Fini() override
    {
        geographic_msgs__msg__GeoPoseWithCovarianceStamped__fini(&geo_pose_with_covariance_stamped_msg);
    }

    virtual const rosidl_message_type_support_t* GetTypeSupport() const override
    {
        return ROSIDL_GET_MSG_TYPE_SUPPORT(geographic_msgs, msg, GeoPoseWithCovarianceStamped);
    }

    UFUNCTION(BlueprintCallable)
    void SetMsg(const FROSGeoPoseWithCovarianceStamped& Input)
    {
        Input.SetROS2(geo_pose_with_covariance_stamped_msg);
    }

    UFUNCTION(BlueprintCallable)
    void GetMsg(FROSGeoPoseWithCovarianceStamped& Output) const
    {
        Output.SetFromROS2(geo_pose_with_covariance_stamped_msg);
    }

    virtual void* Get() override
    {
        return &geo_pose_with_covariance_stamped_msg;
    }

private:
    virtual FString ToString() const override
    {
        /* TODO: Fill here */

        checkNoEntry();
        return FString();
    }

    ros_msg_c_typename geo_pose_with_covariance_stamped_msg;
};
