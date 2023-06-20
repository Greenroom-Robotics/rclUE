#pragma once

#include <CoreMinimal.h>
#include "Conversions.h"
#include "ROS2GenericMsg.h"

#include "action_msgs/msg/goal_status_array.h"


// Include directives for member types
#include "Msgs/ROS2GoalStatus.h"

#include "ROS2GoalStatusArray.generated.h"


USTRUCT(Blueprintable)
struct RCLUE_API FROSGoalStatusArray
{
    GENERATED_BODY()

    using ros_msg_c_typename = action_msgs__msg__GoalStatusArray;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FROSGoalStatus> status_list;
    // rclc type: action_msgs__msg__GoalStatus__Sequence status_list

    void SetFromROS2(const ros_msg_c_typename& in_ros_data)
    {
        status_list = ROS2MsgToUE::FromStructSequence<FROSGoalStatus>(in_ros_data.status_list);
    }

    void SetROS2(ros_msg_c_typename& out_ros_data) const
    {
        UEToROS2Msg::SetStructSequence(status_list, out_ros_data.status_list);
    }
};

UCLASS()
class RCLUE_API UROS2GoalStatusArray : public UROS2GenericMsg
{
    GENERATED_BODY()

    using ros_msg_c_typename = action_msgs__msg__GoalStatusArray;

public:
    virtual void Init() override
    {
        action_msgs__msg__GoalStatusArray__init(&goal_status_array_msg);
    }

    virtual void Fini() override
    {
        action_msgs__msg__GoalStatusArray__fini(&goal_status_array_msg);
    }

    virtual const rosidl_message_type_support_t* GetTypeSupport() const override
    {
        return ROSIDL_GET_MSG_TYPE_SUPPORT(action_msgs, msg, GoalStatusArray);
    }

    UFUNCTION(BlueprintCallable)
    void SetMsg(const FROSGoalStatusArray& Input)
    {
        Input.SetROS2(goal_status_array_msg);
    }

    UFUNCTION(BlueprintCallable)
    void GetMsg(FROSGoalStatusArray& Output) const
    {
        Output.SetFromROS2(goal_status_array_msg);
    }

    virtual void* Get() override
    {
        return &goal_status_array_msg;
    }

private:
    virtual FString ToString() const override
    {
        /* TODO: Fill here */

        checkNoEntry();
        return FString();
    }

    ros_msg_c_typename goal_status_array_msg;
};
