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
}

// Called when the game starts or when spawned
void AEmptyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

