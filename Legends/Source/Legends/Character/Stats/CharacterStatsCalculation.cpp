// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterStatsCalculation.h"

CharacterStatsCalculation::CharacterStatsCalculation() : statModifiers(TArray<StatModifier*>())
{
	//statModifiers = TArray<StatModifier*>();
	//StatModifiers = statModifiers.asreadonly;//TODO
}

CharacterStatsCalculation::CharacterStatsCalculation(float baseValue) : CharacterStatsCalculation()
{
	BaseValue = baseValue;
}

float CharacterStatsCalculation::getValue()
{
	if (isDirty || lastBaseValue != BaseValue)
	{
		lastBaseValue = BaseValue;
		_value = CalculateFinalValue();
		isDirty = false;
	}
	return _value;
}


void CharacterStatsCalculation::AddModifier(StatModifier *mod)
{
	isDirty = true;
	statModifiers.Emplace(mod);
	statModifiers.Sort(); // TODO
}

FORCEINLINE bool operator<(const StatModifier& a, const StatModifier& b)
{
	return a.Order < b.Order;
}

bool CharacterStatsCalculation::RemoveModifier(StatModifier *mod)
{
	if (statModifiers.Remove(mod))
	{
		isDirty = true;
		return true;
	}
	return false;
}


/*int CharacterStatsCalculation::CompareModifierOrder(const StatModifier& a, const StatModifier& b)
{
	if (a.Order < b.Order)
	{
		return -1;
	}
	else if (a->Order > b->Order)
	{
		return 1;
	}
	return 0; // if (a.Order == b.Order)
	return a.Order < b.Order;
}*/

float CharacterStatsCalculation::CalculateFinalValue()
{
	float finalValue = BaseValue;
	float sumPercentAdd = 0; // This will hold the sum of our "PercentAdd" modifiers

	for (int i = 0; i < statModifiers.Num(); i++)
	{
		StatModifier *mod = statModifiers[i];
		
		if (mod->Type == StatModType::Flat)
		{
			finalValue += mod->Value;
		}
		else if (mod->Type == StatModType::PercentAdd) // When we encounter a "PercentAdd" modifier 
		{
			sumPercentAdd += mod->Value; // Start adding together all modifiers of this type

			// If we're at the end of the list OR the next modifer isn't of this type
			if (i + 1 >= statModifiers.Num() || statModifiers[i + 1]->Type != StatModType::PercentAdd) 
			{
				finalValue *= 1 + sumPercentAdd; // Multiply the sum with the "finalValue", like we do for "PercentMult" modifiers
				sumPercentAdd = 0; // Reset the sum back to 0
			}
		}
		else if (mod->Type == StatModType::PercentMult) // Percent renamed to PercentMult            //??????????????
		{
			finalValue *= 1 + mod->Value;
		}
	}
	
	return static_cast<float>(std::round(finalValue * std::pow(10, 4))) / std::pow(10, 4);
}


bool CharacterStatsCalculation::RemoveAllModifiersFromSource(UObject *source)
{
	bool didRemove = false;

	for (int i = statModifiers.Num() - 1; i >= 0; i--)
	{
		if (statModifiers[i]->Source == source)
		{
			isDirty = true;
			didRemove = true;
			statModifiers.RemoveAt(i);
		}
	}
	return didRemove;
}

CharacterStatsCalculation::~CharacterStatsCalculation()
{
}
