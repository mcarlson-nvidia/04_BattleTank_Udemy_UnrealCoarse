// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank *t = GetControlledTank();
	if (t)
	{

		UE_LOG(LogTemp, Warning, TEXT("Got Tank %s."), *t->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Tank."));
	}


}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
