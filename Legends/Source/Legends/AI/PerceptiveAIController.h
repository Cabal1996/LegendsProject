// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Perception/AISenseConfig_Sight.h"

#include "PerceptiveAIController.generated.h"


/**
 * 
 */
UCLASS()
class LEGENDS_API APerceptiveAIController : public AAIController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
	virtual void Possess(APawn* InPawn) override;

public:
	APerceptiveAIController();

	UAISenseConfig_Sight *sightConfig;

	UAIPerceptionComponent *PerceptionComponent;

	TArray<AActor*> enemies;
	UFUNCTION()
	void SenseStuff(const TArray<AActor*>& Actors);
};
