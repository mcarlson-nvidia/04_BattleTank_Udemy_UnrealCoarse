// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	void AimTowardCrosshairs();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookVectorHitLocation(const FVector& Start, const FVector& Direction, FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	FVector2D CrosshairLocation = FVector2D(0.5f, 1.0f / 3.0f);
	
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0;
};
