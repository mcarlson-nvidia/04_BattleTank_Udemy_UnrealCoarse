// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretMeshComponent.h"




void UTurretMeshComponent::Swivel(float RelativeSpeed)
{
	// Move the turret base the correct amount this frame, given max swivel speed.
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	float SwivelChange = RelativeSpeed*MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	float RawNewSwivel = RelativeRotation.Yaw + SwivelChange;
	SetRelativeRotation(FRotator(0, RawNewSwivel, 0));
}
