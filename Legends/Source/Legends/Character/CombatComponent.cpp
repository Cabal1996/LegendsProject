// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatComponent.h"
#include "Character/CharacterStats.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Character/Weapon/Projectile.h"



// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}

void UCombatComponent::Init(UCharacterStats* OwnerStats)
{
	this->OwnerStats = OwnerStats;
	
}

void UCombatComponent::ApplyDamage()
{
	if (!ensure(OwnerStats != nullptr)) return;
	if (!CombatTarget) return;
	
	if (!CombatTarget->ResiveDamage(OwnerStats->damage))
		CombatTarget = nullptr;
}

void UCombatComponent::SpawnProjectile(FTransform SpawnAt, TSubclassOf<AActor> ProjectileType)
{
	UE_LOG(LogTemp, Warning, TEXT("%s "), *SpawnAt.ToString())

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	if (!ensure(ProjectileClass != nullptr)) return;
	FActorSpawnParameters Param;
	Param.Instigator = Cast<APawn>(GetOwner());
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AProjectile* Projectile = World->SpawnActor<AProjectile>(
		ProjectileClass, SpawnAt, Param
	);
	if (!ensure(Projectile != nullptr)) return;
	Projectile->OnProjectileHit.AddDynamic(this, &UCombatComponent::ApplyDamage);
	Projectile->LaunchHomming(CombatTarget->GetOwner()->GetRootComponent());

}

bool UCombatComponent::ResiveDamage(float damageTo)
{	
	if (!ensure(OwnerStats != nullptr)) return false;

	OwnerStats->currentHealth = FMath::Clamp(OwnerStats->currentHealth - damageTo, 0.f, BIG_NUMBER);
	OnDamageRecive.Broadcast();

	if (OwnerStats->currentHealth <= 0)
	{
		TimeToDie.Broadcast();
		return false;
	}

	return true;
}

void UCombatComponent::SetCombatTarget(UCombatComponent* TargetToSet)
{
	CombatTarget = TargetToSet;
}

bool UCombatComponent::IsInAttackRange()
{
	if (!ensure(OwnerStats != nullptr)) return false;
	if (!CombatTarget)
	{
		return false;
	}

	float distanceToTarget = (GetOwner()->GetActorLocation() - CombatTarget->GetOwner()->GetActorLocation()).Size();
	//UE_LOG(LogTemp, Warning, TEXT("Range: %f || Limit: %f"), distanceToTarget, OwnerStats->attackRange)
	return OwnerStats->attackRange > distanceToTarget;
}
