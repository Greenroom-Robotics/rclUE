#pragma once

#include "ROS2Support.h"
#include "ROS2GenericSrv.h"

#include "Service.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FServiceCallback, UROS2GenericSrv*, InService /*Service*/);

USTRUCT(Blueprintable)
struct RCLUE_API FService
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ServiceName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UROS2GenericSrv> ServiceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UROS2GenericSrv* Service = nullptr;

	rcl_service_t rcl_service;

	FServiceCallback Callback;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Ready = false;
};
