// Fill out your copyright notice in the Description page of Project Settings.

#include "BarrelMeshComponent.h"




void UBarrelMeshComponent::Elevate(float RelativeSpeed)
{
	// Move the barrel the right amound this frame, given max elevation speed and frame time.
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	float ElevationChange = RelativeSpeed*MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	SetRelativeRotation(FRotator(FMath::Clamp(RawNewElevation, ElevationRange.GetMin(), ElevationRange.GetMax()), 0, 0));
}
