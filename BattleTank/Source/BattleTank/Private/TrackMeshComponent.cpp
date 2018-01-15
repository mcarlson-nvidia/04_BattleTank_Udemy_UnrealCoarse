// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackMeshComponent.h"




void UTrackMeshComponent::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp(Throttle, -1.0f, 1.0f);
//	UE_LOG(LogTemp, Warning, TEXT("Tank %s throttle %f."), *GetName(), Throttle);

	FVector ForceApplied = GetForwardVector()*Throttle*TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation(); // center lower of track.

	UPrimitiveComponent *Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (Tank)
	{
		Tank->AddForceAtLocation(ForceApplied, ForceLocation);
	}
}
