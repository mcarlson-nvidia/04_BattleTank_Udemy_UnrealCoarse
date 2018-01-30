// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class URadialForceComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	void OnTimerExpire();
public:
	// Sets default values for this actor's properties
	AProjectile();

protected:

	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 10.f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ImpactBlast = nullptr;

	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* ExplosiveForce = nullptr;

	UProjectileMovementComponent* ProjectileMovement = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void LaunchProjectile(float speed);

	
	
private:
};
