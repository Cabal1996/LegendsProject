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
	for (AActor* Actor : PersivedActors)
	{
		if (!Actor || Actor->ActorHasTag(TEXT("Corp")) || !Actor->FindComponentByClass<UCharacterStats>()) continue;
		for (const FName &Tag : GetPawn()->Tags)
		{
			if (!Actor->ActorHasTag(Tag))
			{
				enemies.AddUnique(Actor);
			}
		}
	}

		//
	if (!Blackboard) return enemies;
	Blackboard->SetValueAsBool(TEXT("SeeEnemys"), enemies.Num() != 0);


	return enemies;
}

void APerceptiveAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	Stats = Cast<UCharacterStats>(InPawn->GetComponentByClass(UCharacterStats::StaticClass()));
	if (!ensure(Stats != nullptr)) return;

	sightConfig->SightRadius = Stats->viewDistance;
	sightConfig->LoseSightRadius = (Stats->viewDistance)+25;
	sightConfig->PeripheralVisionAngleDegrees = Stats->viewAngle;
	PerceptionComponent->ConfigureSense(*sightConfig);
}

void APerceptiveAIController::UnPossess()
{
	Super::UnPossess();

	PerceptionComponent->bIsActive = false;
}





