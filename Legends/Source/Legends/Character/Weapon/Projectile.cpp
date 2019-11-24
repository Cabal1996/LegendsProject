// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Colider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereColl"));
	if (!Colider) return;
	SetRootComponent(Colider);
	Colider->SetSphereRadius(15.f);
	Colider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Colider->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchHomming(USceneComponent* HomingTarget)
{
	currentSpeed = InitialSpeed;
	ProjectileTarget = HomingTarget;
}

void AProjectile::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	MoveProjectile(deltaTime);
}

void AProjectile::MoveProjectile(float deltaTime)
{
	if (!ProjectileTarget) return;

	currentSpeed = FMath::Clamp(currentSpeed + Axeleration * deltaTime, 0.f, MaxSpeed);

	FVector TargetLocation = ProjectileTarget->GetComponentLocation();
	FVector CurrentLocation = GetActorLocation();

	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();

	FVector NewLocation = CurrentLocation + (Direction * currentSpeed * deltaTime);

	SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
}

void AProjectile::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	if (!ProjectileTarget) return;
	if (OtherActor->GetRootComponent() == ProjectileTarget)
	{
		OnProjectileHit.Broadcast();
		this->Destroy();
	}
}
