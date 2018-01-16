// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TrackMeshComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTrackMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// Set throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float TrackMaxDrivingForce = 400000; // tank 40k, and 1g acceleration (seems wrong)
};
