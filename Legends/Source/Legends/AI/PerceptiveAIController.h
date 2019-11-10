// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "PerceptiveAIController.generated.h"


class UAISenseConfig_Sight;
class UCharacterStats;
/**
 * 
 */
UCLASS()
class LEGENDS_API APerceptiveAIController : public AAIController
{
	GENERATED_BODY()

public:
	APerceptiveAIController();

	UFUNCTION(BlueprintPure, Category = "Perception")
	TArray<AActor*> GetEnemysInSightRange() const { return enemies; };

	UFUNCTION()
	void SenseStuff(const TArray<AActor*>& Actors);

private:

	UAISenseConfig_Sight *sightConfig;
	UAIPerceptionComponent *PerceptionComponent;
	UCharacterStats* Stats;

	TArray<AActor*> enemies;
	

	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;
};
