// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterStats.h"

// Sets default values for this component's properties
UCharacterStats::UCharacterStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	MAX_health = STR * 2 + WILL;
	currentHealth = MAX_health;
	damage = STR + INT;

	attackSpeed = 1000 / (1000 - AGI * 9);
	moveSpeed = AGI;
	turnSpeed = AGI/5;

	viewDistance = 400 + PER * 100;
	viewAngle = FMath::Clamp((60.f + 3 * ((PER*PER) / 100)), 0.f, 360.f);


}





