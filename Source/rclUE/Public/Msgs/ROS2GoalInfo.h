#pragma once

#include <CoreMinimal.h>
#include "Conversions.h"
#include "ROS2GenericMsg.h"

#include "action_msgs/msg/goal_info.h"


// Include directives for member types
#include "Msgs/ROS2UUID.h"
#include "Msgs/ROS2Time.h"

#include "ROS2GoalInfo.generated.h"


USTRUCT(Blueprintable)
struct RCLUE_API FROSGoalInfo
{
    GENERATED_BODY()

    using ros_msg_c_typename = action_msgs__msg__GoalInfo;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FROSUUID goal_id;
    // rclc type: unique_identifier_msgs__msg__UUID goal_id

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDateTime stamp;
    // rclc type: builtin_interfaces__msg__Time stamp

    void SetFromROS2(const ros_msg_c_typename& in_ros_data)
    {
        goal_id.SetFromROS2(in_ros_data.goal_id);
        stamp = ROS2MsgToUE::From(in_ros_data.stamp);
    }

    void SetROS2(ros_msg_c_typename& out_ros_data) const
    {
        goal_id.SetROS2(out_ros_data.goal_id);
        UEToROS2Msg::Set(stamp, out_ros_data.stamp);
    }
};

UCLASS()
class RCLUE_API UROS2GoalInfo : public UROS2GenericMsg
{
    GENERATED_BODY()

    using ros_msg_c_typename = action_msgs__msg__GoalInfo;

public:
    virtual void Init() override
    {
        action_msgs__msg__GoalInfo__init(&goal_info_msg);
    }

    virtual void Fini() override
    {
        action_msgs__msg__GoalInfo__fini(&goal_info_msg);
    }

    virtual const rosidl_message_type_support_t* GetTypeSupport() const override
    {
        return ROSIDL_GET_MSG_TYPE_SUPPORT(action_msgs, msg, GoalInfo);
    }

    UFUNCTION(BlueprintCallable)
    void SetMsg(const FROSGoalInfo& Input)
    {
        Input.SetROS2(goal_info_msg);
    }

    UFUNCTION(BlueprintCallable)
    void GetMsg(FROSGoalInfo& Output) const
    {
        Output.SetFromROS2(goal_info_msg);
    }

    virtual void* Get() override
    {
        return &goal_info_msg;
    }

private:
    virtual FString ToString() const override
    {
        /* TODO: Fill here */

        checkNoEntry();
        return FString();
    }

    ros_msg_c_typename goal_info_msg;
};
