// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	ATank* player = GetPlayerTank();
	ATank* me = Cast<ATank>(GetPawn());
	if (player && me)
	{
		me->AimAt(player->GetActorLocation());
		me->Fire();
	}
}

ATank* ATankAIController::GetPlayerTank()
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

