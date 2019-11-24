// Fill out your copyright notice in the Description page of Project Settings.

#include "EmptyCharacter.h"

#include "CombatComponent.h"
#include "CharacterStats.h"

// Sets default values
AEmptyCharacter::AEmptyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Stats = CreateDefaultSubobject<UCharacterStats>("Stats");
	if (!ensure(Stats != nullptr)) return;
	Combat = CreateDefaultSubobject<UCombatComponent>("Combat");
	if (!ensure(Combat != nullptr)) return;

	Combat->Init(Stats);
	Combat->TimeToDie.AddDynamic(this, &AEmptyCharacter::Death);
}

void AEmptyCharacter::ApplyDamage()
{
	Combat->ApplyDamage();
}

void AEmptyCharacter::Death()
{
	bIsDead = true;
	
	DetachFromControllerPendingDestroy();

	Stats->DestroyComponent();
	Combat->DestroyComponent();
}

void AEmptyCharacter::SetAttackTarget(AEmptyCharacter* TargetCharacter)
{
	if (!TargetCharacter)
	{
		Combat->SetCombatTarget(nullptr);
	}
	else
	{
		Combat->SetCombatTarget(TargetCharacter->Combat);
	}
	
}

bool AEmptyCharacter::CanAttack()
{
	return Combat->IsInAttackRange();
}

float AEmptyCharacter::GetCurrentHP()
{
	if (Stats->currentHealth <= 0) return 0.f;
	return Stats->currentHealth/Stats->MAX_health;
}

void AEmptyCharacter::ApplyBuff(UObject* buff)
{
	UE_LOG(LogTemp, Warning, TEXT("Buff applied to %s"), *GetName())
}

