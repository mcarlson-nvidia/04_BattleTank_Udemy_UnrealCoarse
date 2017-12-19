// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretAimingComponent.h"

#include "BarrelMeshComponent.h"
#include "TurretMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTurretAimingComponent::UTurretAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTurretAimingComponent::SetBarrel(UBarrelMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTurretAimingComponent::SetTurret(UTurretMeshComponent* TurretToSet)
{
	Turret = TurretToSet;
}

// Called when the game starts
void UTurretAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTurretAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTurretAimingComponent::AimAt(const FVector& Location, float LaunchSpeed)
{
	if (!Barrel || !Turret) return;
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Opening"));
	// Calculate out launch velocity
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		Location,
		LaunchSpeed,
		false,
		0.0f,
		false,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
}

void UTurretAimingComponent::MoveBarrel(const FVector &AimDirection)
{
	if (!Barrel) return;
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimDirectionRotator = AimDirection.Rotation();
	FRotator DeltaRotation = AimDirectionRotator - BarrelRotator;

	Barrel->Elevate(5.0f);// TODO remove magic number

}

