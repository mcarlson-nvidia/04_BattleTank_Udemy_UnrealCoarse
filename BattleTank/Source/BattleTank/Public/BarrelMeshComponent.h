// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "BarrelMeshComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UBarrelMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward, and +1 is max upward movement
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = TurretAiming)
	float MaxDegreesPerSecond = 10;

	UPROPERTY(EditAnywhere, Category = TurretAiming)
	FVector2D ElevationRange = FVector2D(-5.f,45.f);
};
