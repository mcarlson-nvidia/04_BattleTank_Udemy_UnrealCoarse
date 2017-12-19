// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardCrosshairs();
}

void ATankPlayerController::AimTowardCrosshairs()
{	
	ATank* t = Cast<ATank>(GetPawn());
	if (!t) return;
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		t->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX, ViewportSizeY) * CrosshairLocation;
#if 0
	FHitResult HitResult;
	bool bHit = GetHitResultAtScreenPosition(ScreenLocation, ECollisionChannel::ECC_Visibility, false, HitResult);
	if (bHit)
	{
		OutHitLocation = HitResult.ImpactPoint;
		// Draws a red line for debugging purposes
		DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Red);
	}
	return bHit;
#else
	FVector LookDirection;
	FVector CameraWorldLocation;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection))
	{
		return GetLookVectorHitLocation(CameraWorldLocation, LookDirection, OutHitLocation);
	}
	return false;
#endif
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
	}
	return true;
}
