// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EmptyCharacter.generated.h"

class UCharacterStats;
class UCombatComponent;

UCLASS()
class LEGENDS_API AEmptyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEmptyCharacter();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ApplyDamage();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetAttackTarget(AEmptyCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool CanAttack();	

	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetCurrentHP();

	UFUNCTION()
	void Death();
	
	UPROPERTY(VisibleDefaultsOnly, Category = "1Legends")
	UCharacterStats* Stats;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "1Legends")
	UCombatComponent* Combat;
	
	void ApplyBuff(UObject* buff);

private:
	bool bIsDead = false;

	
};
