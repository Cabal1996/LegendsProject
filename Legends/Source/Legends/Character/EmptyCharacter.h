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



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(VisibleDefaultsOnly, Category = "1Legends")
	UCharacterStats* Stats;

	UPROPERTY(VisibleDefaultsOnly, Category = "1Legends")
	UCombatComponent* Combat;

};
