// Fill out your copyright notice in the Description page of Project Settings.

#include "EmptyCharacter.h"

#include "CombatComponent.h"
#include "CharacterStats.h"

// Sets default values
AEmptyCharacter::AEmptyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void AEmptyCharacter::Death_Implementation()
{
	DetachFromControllerPendingDestroy();
}

void AEmptyCharacter::SetAttackTarget(AEmptyCharacter * TargetCahracter)
{
	Combat = TargetCahracter->Combat;
}

// Called when the game starts or when spawned
void AEmptyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

