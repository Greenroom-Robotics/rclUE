#pragma once

#include "Components/SceneCaptureComponent2D.h"

#include "CoreMinimal.h"
#include "NormalSceneCapture.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNormalSceneCapture, Log, All);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class UNREALCAMERACAPTURE_API UNormalSceneCapture : public USceneCaptureComponent2D
{
  GENERATED_UCLASS_BODY()

public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")
  int FrameWidth = 640;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")
  int FrameHeight = 480;

  UPROPERTY(EditAnywhere, Category = "Logging")
  bool VerboseLogging = false;

  // Temporal AA blends reprojected history into each frame, so captured pixels lag
  // the game tick they are stamped with (measured ~4 frames via horizon-solve dt).
  // Disable for cameras whose output feeds time-sensitive consumers (calibration,
  // perception); the capture then falls back to spatial FXAA with motion blur off.
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")
  bool bEnableTemporalAA = true;

  // PostProcessMaterial used for segmentation
  UPROPERTY(EditAnywhere, Category = "Capture")
  UMaterial* PostProcessMaterial = nullptr;

protected:
  virtual void BeginPlay() override;
};
