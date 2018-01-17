// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TurretAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	APawn* player = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* me = GetPawn();
	if (ensure(player && me))
	{
		MoveToActor(player, AcceptanceRadius);
		UTurretAimingComponent *AimingComponent = me->FindComponentByClass<UTurretAimingComponent>();
		if (ensure(AimingComponent))
		{
			AimingComponent->AimAt(player->GetActorLocation());
			if (AimingComponent->GetFiringState() == EFiringState::Locked)
			{
				AimingComponent->Fire();
			}
		}
	}
}

