#include "ROS2Subscriber.h"
#include "ROS2Support.h"

#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>


DEFINE_LOG_CATEGORY(LogROS2Subscriber);

UROS2Subscriber::UROS2Subscriber()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UROS2Subscriber::BeginPlay()
{
    Super::BeginPlay();    
    
    if (bAutoInitialise)
    {
        if (!IsValid(ROSNode))
        {
            AROS2Node* FirstROSNode = Cast<AROS2Node>(UGameplayStatics::GetActorOfClass(GetWorld(), AROS2Node::StaticClass()));
            if (IsValid(FirstROSNode))
            {
                ROSNode = FirstROSNode;
            } else
            {
                UE_LOG(LogROS2Subscriber, Error, TEXT("[%s] Cannot locate a ROSNode Actor to AddPublisher on. Initialisation failed."), *GetName());
                return;
            }
        }
        if (ROSNode->State != UROS2State::Initialized)
        {
            ROSNode->OnNodeInitialised.AddDynamic(this, &UROS2Subscriber::WhenNodeInits);
        } else
        {
            WhenNodeInits();
        }
    }
}

void UROS2Subscriber::Init()
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR("UROS2Subscriber::Init")
    if (State == UROS2State::Initialized) {
        UE_LOG(LogROS2Subscriber, Error, TEXT("[%s] Initialise called when already initialised"), *GetName());
        return;
    }

    UE_LOG(LogROS2Subscriber, Verbose, TEXT("[%s] Initialising..."), *GetName());

    if (!IsValid(ROSNode)) {
        UE_LOG(LogROS2Subscriber, Error, TEXT("[%s] ROS Node is invalid"), *GetName());
        return;
    }

    check(ROSNode->State == UROS2State::Initialized);

    if (State == UROS2State::Created)
    {
        if(TopicName.IsEmpty())
        {
            UE_LOG(LogROS2Subscriber, Error, TEXT("[%s] Topic Name not set. Initialisation failed."), *GetName());
            return;
        }

        if(TopicType == nullptr)
        {
            UE_LOG(LogROS2Subscriber, Error, TEXT("[%s] Topic Type not set. Initialisation failed."), *GetName());
            return;
        }

        TopicMessage = NewObject<UROS2GenericMsg>(this, TopicType);
        check(IsValid(TopicMessage));
        TopicMessage->Init();

        Ready = false;

        FScopeLock lock(ROSNode->GetMutex());

        rcl_subscription = rcl_get_zero_initialized_subscription();

        rcl_subscription_options_t sub_opt = rcl_subscription_get_default_options();
        sub_opt.allocator = ROSNode->ROSSubsystem()->GetRclUEAllocator();
        
        if (bQosOverride) {
            sub_opt.qos = Qos.ToRMW();
        } else {
            sub_opt.qos = QoSProfiles_LUT[QosProfilePreset];
        }

        UE_LOG(LogROS2Subscriber, Display, TEXT("[%s] Subscribing to topic %s"), *GetName(), *TopicName);
        RCSOFTCHECK(rcl_subscription_init(&rcl_subscription, ROSNode->GetRCLNode(), TopicMessage->GetTypeSupport(), TCHAR_TO_UTF8(*TopicName), &sub_opt));

        ROSNode->InvalidateWaitSet();

        State = UROS2State::Initialized;
    }
}

void UROS2Subscriber::Destroy()
{
    UE_LOG(LogROS2Subscriber, Verbose, TEXT("[%s] subscriber destroy start (%s)"), *GetName(), *__LOG_INFO__);
    if (TopicMessage != nullptr)
    {
        TopicMessage->Fini();
    }

    if (ROSNode != nullptr)
    {
        UE_LOG(LogROS2Subscriber, Verbose, TEXT("Subscriber Destroy - rcl_Subscriber_fini (%s)"), *__LOG_INFO__);
        RCSOFTCHECK(rcl_subscription_fini(&rcl_subscription, ROSNode->GetRCLNode()));
    }
    UE_LOG(LogROS2Subscriber, Display, TEXT("[%s] subscriber destroyed"), *GetName());
}

void UROS2Subscriber::HandleMessage(UROS2GenericMsg* Message)
{
    if (IncomingMessageDelegate.IsBound()) {
        IncomingMessageDelegate.Execute(Message);
    } else {
        IncomingMessage(Message);
    }
}

void UROS2Subscriber::IncomingMessage_Implementation(UROS2GenericMsg* Message)
{
    UE_LOG(LogROS2Subscriber, Error, TEXT("[%s] Incoming Message has not been overriden."), *GetName());
}

void UROS2Subscriber::WhenNodeInits()
{
    UE_LOG(LogROS2Subscriber, Verbose, TEXT("[%s] Node is ready!."), *GetName());
    ROSNode->AddSubscriber(this);
}
