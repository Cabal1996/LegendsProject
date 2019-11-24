// Fill out your copyright notice in the Description page of Project Settings.

#include "StatModifier.h"

StatModifier::StatModifier(float value, StatModType type, int order, UObject *source)
{
	Value = value;
	Type = type;
	Order = order;
	Source = source; 
}

StatModifier::StatModifier(float value, StatModType type) : StatModifier(value, type, (int)(type), nullptr)
{
}

StatModifier::StatModifier(float value, StatModType type, int order) : StatModifier(value, type, order, nullptr)
{
}

StatModifier::StatModifier(float value, StatModType type, UObject *source) : StatModifier(value, type, (int)(type), source)
{
}

StatModifier::~StatModifier()
{
	delete &Type;
}
