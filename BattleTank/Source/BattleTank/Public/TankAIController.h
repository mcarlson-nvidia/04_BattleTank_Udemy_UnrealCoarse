// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// How close the AI tank can get
	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	float AcceptanceRadius = 8000; // tank 40k, and 1g acceleration (seems wrong)

private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnPossessedTankDeath();

};
