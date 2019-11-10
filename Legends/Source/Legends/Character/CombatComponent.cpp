// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatComponent.h"
#include "Character/CharacterStats.h"



// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

	CombatTarget->ResiveDamage(OwnerStats->damage);
}

void UCombatComponent::ResiveDamage(float damageTo)
{	
	if (!ensure(OwnerStats != nullptr)) return;
	OwnerStats->currentHealth = FMath::Clamp(CombatTarget->OwnerStats->currentHealth - damageTo, 0.f, BIG_NUMBER);

	if (OwnerStats->currentHealth <= 0)
	{
		TimeToDie.Broadcast();
	}
}

void UCombatComponent::SetCombatTarget(UCombatComponent* TargetToSet)
{
	CombatTarget = TargetToSet;
}



