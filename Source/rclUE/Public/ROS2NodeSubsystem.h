#pragma once

#include "ROS2Subsystem.h"
#include "ROS2Support.h"
#include "rclcUtilities.h"

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <Tickable.h>

#include "Service.h"
// #include "Action.h"

#include "ROS2NodeSubsystem.generated.h"

class UROS2Publisher;
class UROS2Subscriber;
class UROS2ServiceClient;
class UROS2ActionServer;
class UROS2ActionClient;


UCLASS(Blueprintable)
class RCLUE_API UROS2NodeSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
    GENERATED_BODY()

public:
    // UFUNCTION(BlueprintCallable, Category = "ROS2")
    // UROS2Support* GetSupport() const;

    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    virtual void Deinitialize() override;

    virtual void Tick(float DeltaTime) override;

    virtual bool IsTickable() const override;

    virtual bool IsTickableWhenPaused() const override;

    virtual bool IsTickableInEditor() const override;

    virtual TStatId GetStatId() const override;
   
    void InvalidateWaitSet();

    UFUNCTION(BlueprintCallable)
    void AddSubscriber(UROS2Subscriber* Subscriber);

    UFUNCTION(BlueprintCallable)
    void AddPublisher(UROS2Publisher* InPublisher);

    UFUNCTION(BlueprintCallable)
    void RemoveSubscriber(UROS2Subscriber* Subscriber);

    UFUNCTION(BlueprintCallable)
    void RemovePublisher(UROS2Publisher* Publisher);

    UFUNCTION(BlueprintCallable)
    void AddServiceClient(UROS2ServiceClient* InClient);

    UFUNCTION(BlueprintCallable)
    void AddServiceServer(const FString& ServiceName,
                          const TSubclassOf<UROS2GenericSrv> SrvClass,
                          const FServiceCallback& Callback);

    UFUNCTION(BlueprintCallable)
    void AddActionClient(UROS2ActionClient* InActionClient);

    UFUNCTION(BlueprintCallable)
    void AddActionServer(UROS2ActionServer* InActionServer);

    UPROPERTY(BlueprintReadOnly)
    UROS2State State = UROS2State::Created;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name = TEXT("node");

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Namespace = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool InitialiseOnBeginPlay = true;

    // wait_set quantities - currently unused
    UPROPERTY(VisibleAnywhere, Category = "Diagnostics")
    int NGuardConditions = 0;

    UPROPERTY(VisibleAnywhere, Category = "Diagnostics")
    int NTimers = 0;

    UPROPERTY(VisibleAnywhere, Category = "Diagnostics")
    int NEvents = 0;

    // UPROPERTY(BlueprintAssignable)
    // FOnNodeInitialisedDelegate OnNodeInitialised;

    UROS2Subsystem* ROSSubsystem()
    {
        return GetGameInstance()->GetSubsystem<UROS2Subsystem>();
    }
    
    FCriticalSection* GetMutex()
    {
        return &(ROSSubsystem()->RCLCritical);
    }
    
    rcl_node_t* GetRCLNode()
    {
        return &_rcl_node;
    }

    UPROPERTY(BlueprintReadWrite)
    TArray<UROS2Subscriber*> Subscribers;
    
    UPROPERTY(BlueprintReadWrite)
    TArray<UROS2Publisher*> Publishers;
    
protected:
    // method used to wait on communication and call delegates when appropriate
    // modeled after executor + actions
    UFUNCTION()
    void SpinSome();

    rcl_node_t _rcl_node;
    rcl_wait_set_t wait_set;

    UPROPERTY()
    UROS2Support* Support;

    UPROPERTY(BlueprintReadWrite)
    TArray<FService> Services;

    UPROPERTY(BlueprintReadWrite)
    TArray<UROS2ServiceClient*> Clients;

    UPROPERTY(BlueprintReadWrite)
    TArray<UROS2ActionClient*> ActionClients;

    UPROPERTY(BlueprintReadWrite)
    TArray<UROS2ActionServer*> ActionServers;

    UPROPERTY()
    FTimerHandle TimerHandle;

private:
    // these 3 methods are based on _rclc_default_scheduling of the rclc executor
    UFUNCTION()
    void HandleSubscribers();

    UFUNCTION()
    void HandleServices();

    UFUNCTION()
    void HandleClients();
};
