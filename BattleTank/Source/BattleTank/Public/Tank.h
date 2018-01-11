// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTurretAimingComponent;
class UBarrelMeshComponent;
class UTurretMeshComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UBarrelMeshComponent* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurret(UTurretMeshComponent* TurretToSet);

	void AimAt(const FVector& Location);
	
	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	UTurretAimingComponent* TurretAimingComponent = nullptr;

private:	
	// Sets default values for this pawn's properties
	ATank();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UBarrelMeshComponent * Barrel = nullptr;
};
