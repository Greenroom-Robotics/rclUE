#pragma once

#include <CoreMinimal.h>
#include "Conversions.h"
#include "ROS2GenericMsg.h"

#include "example_interfaces/msg/int8.h"



#include "ROS2Int8.generated.h"


USTRUCT(Blueprintable)
struct RCLUE_API FROSInt8
{
    GENERATED_BODY()

    using ros_msg_c_typename = example_interfaces__msg__Int8;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int data = 0;
    // rclc type: int8_t data

    void SetFromROS2(const ros_msg_c_typename& in_ros_data)
    {
        data = in_ros_data.data;
    }

    void SetROS2(ros_msg_c_typename& out_ros_data) const
    {
        out_ros_data.data = data;
    }
};

UCLASS()
class RCLUE_API UROS2Int8 : public UROS2GenericMsg
{
    GENERATED_BODY()

    using ros_msg_c_typename = example_interfaces__msg__Int8;

public:
    virtual void Init() override
    {
        example_interfaces__msg__Int8__init(&int8_msg);
    }

    virtual void Fini() override
    {
        example_interfaces__msg__Int8__fini(&int8_msg);
    }

    virtual const rosidl_message_type_support_t* GetTypeSupport() const override
    {
        return ROSIDL_GET_MSG_TYPE_SUPPORT(example_interfaces, msg, Int8);
    }

    UFUNCTION(BlueprintCallable)
    void SetMsg(const FROSInt8& Input)
    {
        Input.SetROS2(int8_msg);
    }

    UFUNCTION(BlueprintCallable)
    void GetMsg(FROSInt8& Output) const
    {
        Output.SetFromROS2(int8_msg);
    }

    virtual void* Get() override
    {
        return &int8_msg;
    }

private:
    virtual FString ToString() const override
    {
        /* TODO: Fill here */

        checkNoEntry();
        return FString();
    }

    ros_msg_c_typename int8_msg;
};
