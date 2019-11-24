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
	UPROPERTY(BlueprintReadOnly, Category = "Implicit")
	int LUCK{ 5 };
	UPROPERTY(BlueprintReadOnly, Category = "Implicit")
	int STR{ 5 };
	UPROPERTY(BlueprintReadOnly, Category = "Implicit")
	int AGI{ 5 };
	UPROPERTY(BlueprintReadOnly, Category = "Implicit")
	int PER{ 5 };
	UPROPERTY(BlueprintReadOnly, Category = "Implicit")
	int WILL{ 5 };
	UPROPERTY(BlueprintReadOnly, Category = "Implicit")
	int INT{ 5 };
	

public:

	float currentHealth;

	float MAX_health;
	float damage;
	float attackSpeed;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float attackRange { 300 }; //TODO make Weapons

	float moveSpeed;
	float turnSpeed;

	float viewDistance;
	float viewAngle;
	

		
};
