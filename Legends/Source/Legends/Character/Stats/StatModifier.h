// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"

enum class StatModType
{
	Flat = 100,
	PercentAdd = 200,
	PercentMult = 300
};

/**
 * 
 */
class UObject;

class LEGENDS_API StatModifier
{
public:
	float Value;
	StatModType Type;//TODO
	int Order;
	UObject *Source = nullptr;//TODO ????


	StatModifier(float value, StatModType type, int order, UObject *source); //TODO
	StatModifier(float value, StatModType type);
	StatModifier(float value, StatModType type, int order);
	StatModifier(float value, StatModType type, UObject *source);
	~StatModifier();
};
