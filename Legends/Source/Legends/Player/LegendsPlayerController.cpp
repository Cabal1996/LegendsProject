// Fill out your copyright notice in the Description page of Project Settings.

#include "LegendsPlayerController.h"
#include "Character/EmptyCharacter.h"

void ALegendsPlayerController::ApplyBuffToHero(bool &Resault)
{
	Resault = false;
	FHitResult Hit;
	bool IsDetected = GetHitResultUnderCursor(
		ECollisionChannel::ECC_Pawn,
		false,
		Hit
	);
	if (IsDetected && Hit.Actor.IsValid())
	{
		AEmptyCharacter* Cahracter = Cast<AEmptyCharacter>(Hit.Actor);
		if (!Cahracter) return;
		Cahracter->ApplyBuff(Buff);
		Resault = true;
	}
	
}
