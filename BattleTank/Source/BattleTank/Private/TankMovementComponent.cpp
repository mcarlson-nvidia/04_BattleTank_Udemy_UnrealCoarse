// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TrackMeshComponent.h"



void UTankMovementComponent::Initialize(UTrackMeshComponent* LeftTrackToSet, UTrackMeshComponent *RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (LeftTrack) LeftTrack->SetThrottle(Throw);
	if (RightTrack) RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (LeftTrack) LeftTrack->SetThrottle(Throw);
	if (RightTrack) RightTrack->SetThrottle(-Throw);
}
