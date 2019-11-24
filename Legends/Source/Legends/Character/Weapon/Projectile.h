// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProjectileHits);

UCLASS()
class LEGENDS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void LaunchHomming(USceneComponent* HomingTarget);

	virtual void Tick(float deltaTime) override;

	FOnProjectileHits OnProjectileHit;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float InitialSpeed { 500 };

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float MaxSpeed { 5000 };

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float Axeleration { 1000 };

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void MoveProjectile(float deltaTime);

	float currentSpeed;
	USceneComponent* ProjectileTarget = nullptr;
	
	UPROPERTY()
	USphereComponent* Colider;
};
