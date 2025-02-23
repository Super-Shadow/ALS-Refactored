﻿#pragma once

#include "AlsRagdollingSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsRagdollingSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStartRagdollingOnLand{true};

	// If character landed with a speed greater than specified value, then start ragdolling.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bStartRagdollingOnLand"))
	float RagdollingOnLandSpeedThreshold{1000.0f};
};
