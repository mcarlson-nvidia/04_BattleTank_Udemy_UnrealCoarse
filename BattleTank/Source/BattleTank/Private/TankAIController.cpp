// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* t = GetPlayerTank();
	if (t)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank %s found player %s."), *GetPawn()->GetName(), *t->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller %s can't find the player tank."), *GetName());
	}
	

}

ATank* ATankAIController::GetPlayerTank()
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

