// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LegendsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LEGENDS_API ALegendsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	UObject* Buff;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void ApplyBuffToHero(bool &Resault);
};
