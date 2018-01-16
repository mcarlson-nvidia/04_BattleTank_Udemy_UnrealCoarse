// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UBarrelMeshComponent;
class UTankMovementComponent;
class UTurretAimingComponent;
class UTurretMeshComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrel(UBarrelMeshComponent* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTurret(UTurretMeshComponent* TurretToSet);

	void AimAt(const FVector& Location);
	
	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTurretAimingComponent* TurretAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTankMovementComponent *TankMovementComponent = nullptr;

private:	
	// Sets default values for this pawn's properties
	ATank();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UBarrelMeshComponent * Barrel = nullptr;
	double LastFireTime = 0;
};
