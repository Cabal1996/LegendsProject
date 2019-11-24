// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <limits>
#include <cmath>
#include "StatModifier.h"
#include "CoreMinimal.h"

/**
 * 
 */
class UObject;
class StatModifier;

class LEGENDS_API CharacterStatsCalculation
{
public:
	CharacterStatsCalculation();//TODO
	CharacterStatsCalculation(float baseValue);

	float BaseValue = 0;
	float getValue();

private:
	//TArray <StatModifier*> StatModifiers;

//protected:
	bool isDirty = true;
	float lastBaseValue = 0;
	float _value = 0;

	TArray <StatModifier*> statModifiers;

public:
	virtual void AddModifier(StatModifier *mod);
	virtual bool RemoveModifier(StatModifier *mod);
	virtual bool RemoveAllModifiersFromSource(UObject *source);//TODO

protected:
	//virtual int CompareModifierOrder(const StatModifier& a, const StatModifier& b);
	virtual float CalculateFinalValue();
	virtual ~CharacterStatsCalculation();
};
