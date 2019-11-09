// Fill out your copyright notice in the Description page of Project Settings.

#include "PerceptiveAIController.h"

#include"Perception/AIPerceptionComponent.h"

void APerceptiveAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void APerceptiveAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);


}

APerceptiveAIController::APerceptiveAIController()
{

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	if (!ensure(PerceptionComponent != nullptr)) return;

	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (!ensure(sightConfig != nullptr)) return;

	PerceptionComponent->ConfigureSense(*sightConfig);
	PerceptionComponent->SetDominantSense(sightConfig->GetSenseImplementation());
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &APerceptiveAIController::SenseStuff);
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	sightConfig->SightRadius = 300;//TODO use stats possessedUnit->sightRange;
	sightConfig->LoseSightRadius = 300;//TODO stats
	sightConfig->PeripheralVisionAngleDegrees = 360.0f;//TODO stats
	PerceptionComponent->ConfigureSense(*sightConfig);
}


void APerceptiveAIController::SenseStuff(const TArray<AActor*>& Actors)
{
	TArray<AActor*> PersivedActors;
	PerceptionComponent->GetPerceivedActors(sightConfig->GetSenseImplementation(), PersivedActors);
	enemies.Empty();
	for (AActor* Actor : PersivedActors)
	{
		if (!Actor || Actor==GetPawn()) continue;
		for (const FName &Tag : GetPawn()->Tags)
		{
			if (!Actor->ActorHasTag(Tag))
			{
				enemies.AddUnique(Actor);
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("I See %i Actors and %i enemies"), PersivedActors.Num(), enemies.Num())
}




