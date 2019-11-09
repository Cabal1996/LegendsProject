// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStats.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEGENDS_API UCharacterStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStats();

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	int LUCK{ 5 };
	int STR{ 5 };
	int AGI{ 5 };
	int PER{ 5 };
	int WILL{ 5 };
	int INT{ 5 };

public:

	float currentHealth;

	float MAX_health;
	float damage;
	float attackSpeed;

	float moveSpeed;
	float turnSpeed;

	float viewDistance;
	float viewAngle;
	

		
};
