#pragma once

#include <CoreMinimal.h>
#include "Conversions.h"
#include "ROS2GenericMsg.h"

#include "action_msgs/msg/goal_status.h"


// Include directives for member types
#include "Msgs/ROS2GoalInfo.h"

#include "ROS2GoalStatus.generated.h"


UENUM(BlueprintType)
enum class UROSGoalStatusStatusEnum : uint8
{
    STATUS_UNKNOWN = 0,
    STATUS_ACCEPTED = 1,
    STATUS_EXECUTING = 2,
    STATUS_CANCELING = 3,
    STATUS_SUCCEEDED = 4,
    STATUS_CANCELED = 5,
    STATUS_ABORTED = 6
};

USTRUCT(Blueprintable)
struct RCLUE_API FROSGoalStatus
{
    GENERATED_BODY()

    using ros_msg_c_typename = action_msgs__msg__GoalStatus;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FROSGoalInfo goal_info;
    // rclc type: action_msgs__msg__GoalInfo goal_info

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UROSGoalStatusStatusEnum status = UROSGoalStatusStatusEnum::STATUS_UNKNOWN;
    // rclc type: int8_t status

    void SetFromROS2(const ros_msg_c_typename& in_ros_data)
    {
        goal_info.SetFromROS2(in_ros_data.goal_info);
        status = static_cast<UROSGoalStatusStatusEnum>(in_ros_data.status);
    }

    void SetROS2(ros_msg_c_typename& out_ros_data) const
    {
        goal_info.SetROS2(out_ros_data.goal_info);
        out_ros_data.status = static_cast<uint8>(status);
    }
};

UCLASS()
class RCLUE_API UROS2GoalStatus : public UROS2GenericMsg
{
    GENERATED_BODY()

    using ros_msg_c_typename = action_msgs__msg__GoalStatus;

public:
    virtual void Init() override
    {
        action_msgs__msg__GoalStatus__init(&goal_status_msg);
    }

    virtual void Fini() override
    {
        action_msgs__msg__GoalStatus__fini(&goal_status_msg);
    }

    virtual const rosidl_message_type_support_t* GetTypeSupport() const override
    {
        return ROSIDL_GET_MSG_TYPE_SUPPORT(action_msgs, msg, GoalStatus);
    }

    UFUNCTION(BlueprintCallable)
    void SetMsg(const FROSGoalStatus& Input)
    {
        Input.SetROS2(goal_status_msg);
    }

    UFUNCTION(BlueprintCallable)
    void GetMsg(FROSGoalStatus& Output) const
    {
        Output.SetFromROS2(goal_status_msg);
    }

    virtual void* Get() override
    {
        return &goal_status_msg;
    }

private:
    virtual FString ToString() const override
    {
        /* TODO: Fill here */

        checkNoEntry();
        return FString();
    }

    ros_msg_c_typename goal_status_msg;
};
