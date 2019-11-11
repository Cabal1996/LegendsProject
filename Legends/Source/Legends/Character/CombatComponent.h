// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class UCharacterStats;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMortalCall);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetHit);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEGENDS_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

	void Init(UCharacterStats* OwnerStats);
	
	void ApplyDamage();
	void SetCombatTarget(UCombatComponent* TargetToSet);

	bool IsInAttackRange();

	bool HaveTarget() { return CombatTarget != nullptr; };

	//UPROPERTY(BlueprintAssignable)
	FMortalCall TimeToDie;

	UPROPERTY(BlueprintAssignable)
	FGetHit OnDamageRecive;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	bool ResiveDamage(float damageTo);

private:

	UCharacterStats* OwnerStats;
	UCombatComponent* CombatTarget;
};
