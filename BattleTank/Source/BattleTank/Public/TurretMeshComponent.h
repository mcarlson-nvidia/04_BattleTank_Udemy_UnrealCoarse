// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TurretMeshComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTurretMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max Left, and +1 is Right movement
	void Swivel(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "TurretAiming")
	float MaxDegreesPerSecond = 25;
	
};
