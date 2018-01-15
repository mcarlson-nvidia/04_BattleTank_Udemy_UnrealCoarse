// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "BarrelMeshComponent.h"
#include "TankMovementComponent.h"
#include "TurretAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TurretAimingComponent = CreateDefaultSubobject<UTurretAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	AController *c = GetController();
	if (!c)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank %s has no controller."), *GetName());
	}
	
}

void ATank::SetBarrel(UBarrelMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
	TurretAimingComponent->SetBarrel(BarrelToSet);
}

void ATank::SetTurret(UTurretMeshComponent* TurretToSet)
{
	TurretAimingComponent->SetTurret(TurretToSet);
}

void ATank::AimAt(const FVector& Location)
{
	TurretAimingComponent->AimAt(Location, LaunchSpeed);
}

void ATank::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s Fired 1"), *GetName());
	if (Barrel)
	{
		double curTime = FPlatformTime::Seconds();
		bool isReloaded = (curTime - LastFireTime) > ReloadTimeInSeconds;

		if (isReloaded)
		{
		UE_LOG(LogTemp, Warning, TEXT("Tank %s Fired 2 %f %f %f"), *GetName(), curTime,LastFireTime,ReloadTimeInSeconds);

			//UE_LOG(LogTemp, Warning, TEXT("Tank %s Fired 3"), *GetName());
			LastFireTime = curTime;
			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Opening")),
				Barrel->GetSocketRotation(FName("Opening")));
			if (Projectile)
			{

				UE_LOG(LogTemp, Warning, TEXT("Tank %s Fired 4"), *GetName());
				Projectile->LaunchProjectile(LaunchSpeed);
			}
		}
	}
}

