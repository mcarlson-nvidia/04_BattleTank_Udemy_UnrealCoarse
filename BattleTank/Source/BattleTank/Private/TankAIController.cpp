// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TurretAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (ensure(PossessedTank))
		{
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
		}
	}
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

void ATankAIController::OnPossessedTankDeath()
{
	if (GetPawn())
	{
		GetPawn()->DetachFromControllerPendingDestroy();
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController::Received death"));
	}
}

