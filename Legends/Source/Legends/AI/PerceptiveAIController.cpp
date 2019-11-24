// Fill out your copyright notice in the Description page of Project Settings.

#include "PerceptiveAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Character/CharacterStats.h"

APerceptiveAIController::APerceptiveAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	if (!ensure(PerceptionComponent != nullptr)) return;

	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (!ensure(sightConfig != nullptr)) return;

	PerceptionComponent->ConfigureSense(*sightConfig);
	PerceptionComponent->SetDominantSense(sightConfig->GetSenseImplementation());
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	
}

TArray<AActor*> APerceptiveAIController::GetEnemysInSightRange()
{
	TArray<AActor*> PersivedActors;
	
	PerceptionComponent->GetPerceivedActors(sightConfig->GetSenseImplementation(), PersivedActors);
	enemies.Empty();
	if (!ControlledPawn) return enemies;
	for (AActor* Actor : PersivedActors)
	{
		if (!Actor || Actor->ActorHasTag(TEXT("Corp")) || !Actor->FindComponentByClass<UCharacterStats>()) continue;
		for (const FName &Tag : ControlledPawn->Tags)
		{
			if (!Actor->ActorHasTag(Tag))
			{
				enemies.AddUnique(Actor);
			}
		}
	}

		//
	if (!Blackboard) return enemies;
	if (enemies.Num() != 0)
	{
		Blackboard->SetValueAsBool(TEXT("SeeEnemys"), true);
	}
	else
	{
		Blackboard->ClearValue(TEXT("SeeEnemys"));
	}
	
	return enemies;
}

AActor* APerceptiveAIController::GetClosestEnemy()
{
	AActor* ClosestEnemy = nullptr;
	if (!ControlledPawn) return ClosestEnemy;
	GetEnemysInSightRange();
	if (enemies.Num() == 0) return ClosestEnemy;
	
	for (int i = 0; i < enemies.Num(); i++)
	{
		if (!enemies[i]) continue;
		if (!ClosestEnemy)
		{
			ClosestEnemy = enemies[i];
			continue;
		}

		if (
			(ControlledPawn->GetActorLocation() - ClosestEnemy->GetActorLocation()).Size()
			/*------------------------------->*/>
			(ControlledPawn->GetActorLocation() - enemies[i]->GetActorLocation()).Size()
			)
			ClosestEnemy = enemies[i];
	}

	return ClosestEnemy;
}

void APerceptiveAIController::SeeEnemy(const TArray<AActor*>& others)
{
	if (!Blackboard) return;
	for (AActor* Other : others)
	{
		
		if (!Other) continue;
		if (!Other->FindComponentByClass<UCharacterStats>()) continue;
		if (Other->ActorHasTag(TEXT("Corp"))) continue;
		for (const FName &Tag : ControlledPawn->Tags)
		{
			if (!Other->ActorHasTag(Tag))
			{
				Blackboard->SetValueAsBool(TEXT("SeeEnemys"), true);
			}
		}
	}
}

void APerceptiveAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	if (!InPawn) return;
	ControlledPawn = InPawn;
	Stats = Cast<UCharacterStats>(InPawn->GetComponentByClass(UCharacterStats::StaticClass()));
	if (!ensure(Stats != nullptr)) return;

	sightConfig->SightRadius = Stats->viewDistance;
	sightConfig->LoseSightRadius = (Stats->viewDistance)+25;
	sightConfig->PeripheralVisionAngleDegrees = Stats->viewAngle;
	PerceptionComponent->ConfigureSense(*sightConfig);
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &APerceptiveAIController::SeeEnemy);
}

void APerceptiveAIController::UnPossess()
{
	Super::UnPossess();
	ControlledPawn = nullptr;
	PerceptionComponent->bIsActive = false;
}
