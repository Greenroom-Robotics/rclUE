#pragma once

#include <CoreMinimal.h>
#include "Conversions.h"
#include "ROS2GenericMsg.h"

#include "geographic_msgs/msg/geo_pose_with_covariance.h"


// Include directives for member types
#include "Msgs/ROS2GeoPose.h"

#include "ROS2GeoPoseWithCovariance.generated.h"


USTRUCT(Blueprintable)
struct RCLUE_API FROSGeoPoseWithCovariance
{
    GENERATED_BODY()

    using ros_msg_c_typename = geographic_msgs__msg__GeoPoseWithCovariance;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FROSGeoPose pose;
    // rclc type: geographic_msgs__msg__GeoPose pose

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<double> covariance = ArrayInitialisers::FloatArray<double>(36);
    // rclc type: double covariance[36]

    void SetFromROS2(const ros_msg_c_typename& in_ros_data)
    {
        pose.SetFromROS2(in_ros_data.pose);
        covariance = ROS2MsgToUE::FromArray(in_ros_data.covariance);
    }

    void SetROS2(ros_msg_c_typename& out_ros_data) const
    {
        pose.SetROS2(out_ros_data.pose);
        UEToROS2Msg::SetSequence(covariance, out_ros_data.covariance);
    }
};

UCLASS()
class RCLUE_API UROS2GeoPoseWithCovariance : public UROS2GenericMsg
{
    GENERATED_BODY()

    using ros_msg_c_typename = geographic_msgs__msg__GeoPoseWithCovariance;

public:
    virtual void Init() override
    {
        geographic_msgs__msg__GeoPoseWithCovariance__init(&geo_pose_with_covariance_msg);
    }

    virtual void Fini() override
    {
        geographic_msgs__msg__GeoPoseWithCovariance__fini(&geo_pose_with_covariance_msg);
    }

    virtual const rosidl_message_type_support_t* GetTypeSupport() const override
    {
        return ROSIDL_GET_MSG_TYPE_SUPPORT(geographic_msgs, msg, GeoPoseWithCovariance);
    }

    UFUNCTION(BlueprintCallable)
    void SetMsg(const FROSGeoPoseWithCovariance& Input)
    {
        Input.SetROS2(geo_pose_with_covariance_msg);
    }

    UFUNCTION(BlueprintCallable)
    void GetMsg(FROSGeoPoseWithCovariance& Output) const
    {
        Output.SetFromROS2(geo_pose_with_covariance_msg);
    }

    virtual void* Get() override
    {
        return &geo_pose_with_covariance_msg;
    }

private:
    virtual FString ToString() const override
    {
        /* TODO: Fill here */

        checkNoEntry();
        return FString();
    }

    ros_msg_c_typename geo_pose_with_covariance_msg;
};
