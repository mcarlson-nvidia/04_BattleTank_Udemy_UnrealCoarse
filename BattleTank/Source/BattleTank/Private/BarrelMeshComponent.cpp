// Fill out your copyright notice in the Description page of Project Settings.

#include "BarrelMeshComponent.h"




void UBarrelMeshComponent::Elevate(float DegreesPerSecond)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Aiming At %f."), *GetOwner()->GetName(), DegreesPerSecond);

}
