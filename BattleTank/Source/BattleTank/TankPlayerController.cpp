// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "TurretAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UTurretAimingComponent *AimingComp = GetPawn()->FindComponentByClass<UTurretAimingComponent>();
	if (ensure(AimingComp))
	{
		FoundAimingComponent(AimingComp);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController::BeginPlay can't find aiming component."));
	}

}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardCrosshairs();
}

void ATankPlayerController::AimTowardCrosshairs()
{
	if (!GetPawn()) return;
	UTurretAimingComponent *AimingComp = GetPawn()->FindComponentByClass<UTurretAimingComponent>();
	if (!ensure(AimingComp)) return;
	FVector HitLocation;
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation)
	{
		AimingComp->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX, ViewportSizeY) * CrosshairLocation;

	FVector LookDirection;
	FVector CameraWorldLocation;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection))
	{
		return GetLookVectorHitLocation(CameraWorldLocation, LookDirection, OutHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& Start, const FVector& Direction, FVector& OutHitLocation) const
{
	struct FHitResult OutHit;
	FVector End = Start + Direction*LineTraceRange;
	OutHitLocation = End;
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(GetPawn());
	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility, Params))
	{
		OutHitLocation = OutHit.Location;
		return true;
	}
	return false;
}
