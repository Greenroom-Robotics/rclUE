// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from nav_msgs/GetPlan.srv - do not modify

#include "Srvs/ROS2GetPlanSrv.h"

const rosidl_service_type_support_t* UROS2GetPlanSrv::GetTypeSupport() const
{
    return ROSIDL_GET_SRV_TYPE_SUPPORT(nav_msgs, srv, GetPlan);
}

void UROS2GetPlanSrv::Init()
{
    nav_msgs__srv__GetPlan_Request__init(&GetPlan_req);
    nav_msgs__srv__GetPlan_Response__init(&GetPlan_res);
}

void UROS2GetPlanSrv::Fini()
{
    nav_msgs__srv__GetPlan_Request__fini(&GetPlan_req);
    nav_msgs__srv__GetPlan_Response__fini(&GetPlan_res);
}

void UROS2GetPlanSrv::SetRequest(const FROSGetPlan_Request& Request)
{
    Request.SetROS2(GetPlan_req);
}

void UROS2GetPlanSrv::GetRequest(FROSGetPlan_Request& Request) const
{
    Request.SetFromROS2(GetPlan_req);
}

void UROS2GetPlanSrv::SetResponse(const FROSGetPlan_Response& Response)
{
    Response.SetROS2(GetPlan_res);
}

void UROS2GetPlanSrv::GetResponse(FROSGetPlan_Response& Response) const
{
    Response.SetFromROS2(GetPlan_res);
}

void* UROS2GetPlanSrv::GetRequest()
{
    return &GetPlan_req;
}

void* UROS2GetPlanSrv::GetResponse()
{
    return &GetPlan_res;
}

FString UROS2GetPlanSrv::SrvRequestToString() const
{
    /* TODO: Fill here */
	checkNoEntry();
    return FString();
}

FString UROS2GetPlanSrv::SrvResponseToString() const
{
    /* TODO: Fill here */
	checkNoEntry();
    return FString();
}