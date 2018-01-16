// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurretAimingComponent.generated.h"

class UBarrelMeshComponent;
class UTurretMeshComponent;

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTurretAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTurretAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UBarrelMeshComponent* BarrelToSet, UTurretMeshComponent* TurretToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(const FVector& Location, float LaunchSpeed);		

private:
	UBarrelMeshComponent *Barrel = nullptr;
	UTurretMeshComponent *Turret = nullptr;

	void MoveTurretAndBarrel(const FVector &AimDirection, bool DoElevate = true);

};
