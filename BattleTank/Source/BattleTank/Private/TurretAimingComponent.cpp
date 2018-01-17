// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretAimingComponent.h"
#include "BarrelMeshComponent.h"
#include "Projectile.h"
#include "TurretMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTurretAimingComponent::UTurretAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTurretAimingComponent::Initialize(UBarrelMeshComponent* BarrelToSet, UTurretMeshComponent* TurretToSet)
{
	Barrel = BarrelToSet;
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

void UTurretAimingComponent::AimAt(const FVector& Location)
{
	if (!ensure(Barrel && Turret)) return;
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
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if (bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTurretAndBarrel(AimDirection, true);
	}
}

void UTurretAimingComponent::MoveTurretAndBarrel(const FVector &AimDirection, bool DoElevate /*= true*/)
{
	if (!ensure(Barrel && Turret)) return;
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimDirectionRotator = AimDirection.Rotation();
	FRotator DeltaRotation = AimDirectionRotator - BarrelRotator;

	if (DoElevate) Barrel->Elevate(DeltaRotation.Pitch);
	Turret->Swivel(DeltaRotation.Yaw);


}

void UTurretAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) return;
	double curTime = FPlatformTime::Seconds();
	bool isReloaded = (curTime - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Tank %s Fired 3"), *GetName());
		LastFireTime = curTime;
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Opening")),
			Barrel->GetSocketRotation(FName("Opening")));
		if (ensure(Projectile))
		{
			Projectile->LaunchProjectile(LaunchSpeed);
		}
	}
}
