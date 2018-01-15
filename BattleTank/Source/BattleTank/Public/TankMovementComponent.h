// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTrackMeshComponent;

/**
 * Resposible foe driging the tant tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTrackMeshComponent* LeftTrackToSet, UTrackMeshComponent *RightTrackToSet); // need to call this in BP because we didn't add an inherited component.

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw);// control throw

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);// control throw
	
private:
	UTrackMeshComponent *LeftTrack = nullptr;
	UTrackMeshComponent *RightTrack = nullptr;
};
