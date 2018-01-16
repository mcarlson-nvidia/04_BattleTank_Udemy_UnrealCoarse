// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTurretAimingComponent;

/**
 * Helps the player aim and move.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank *GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTurretAimingComponent* AimCompRef);

private:
	void AimTowardCrosshairs();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookVectorHitLocation(const FVector& Start, const FVector& Direction, FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	FVector2D CrosshairLocation = FVector2D(0.5f, 1.0f / 3.0f);
	
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0;
};
