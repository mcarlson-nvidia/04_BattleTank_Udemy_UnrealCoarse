// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackMeshComponent.h"




UTrackMeshComponent::UTrackMeshComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTrackMeshComponent::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTrackMeshComponent::OnHit);
}

void UTrackMeshComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.0f;
}
void UTrackMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTrackMeshComponent::ApplySidewaysForce()
{
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work-out the required acceleration this frame to correct
	FVector CorrectionAcceleration = -SlippageSpeed / GetWorld()->DeltaTimeSeconds * GetRightVector();

	// Calculate and apply sideways (F = m a)
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if (ensure(TankRoot))
	{
		FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2.0f; // Two tracks
		TankRoot->AddForce(CorrectionForce);
	}
}

void UTrackMeshComponent::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0f, +1.0f);
}

void UTrackMeshComponent::DriveTrack()
{
	FVector ForceApplied = GetForwardVector()*CurrentThrottle*TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation(); // center lower of track.

	UPrimitiveComponent *Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (ensure(Tank))
	{
		Tank->AddForceAtLocation(ForceApplied, ForceLocation);
	}
}
