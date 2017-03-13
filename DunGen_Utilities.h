// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DunGen_WorldSettings.h"
#include "DunGen_Map.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DunGen_Utilities.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DUNGEN_API UDunGen_Utilities 
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// Randomizer interaction
	UFUNCTION(BlueprintCallable, Category = "DunGen|Randomizer")
		static bool SetRandomizerSeed(ERandomizerEnum Randomizer, int seed);

	UFUNCTION(BlueprintCallable, Category = "DunGen|Randomizer")
		static int32 GetRandomizerSeed(ERandomizerEnum Randomizer);

	UFUNCTION(BlueprintCallable, Category = "DunGen|Randomizer")
		static int32 RandomizeAtPosition(ERandomizerEnum Randomizer, int32 PositionX, int32 PositionY);

	UFUNCTION(BlueprintCallable, Category = "DunGen|Randomizer")
		static int32 RandomizeFromKey(ERandomizerEnum Randomizer, int32 Key);

	UFUNCTION(BlueprintCallable, Category = "DunGen|Randomizer")
		static int32 RandomizeInRange(ERandomizerEnum Randomizer, int32 min, int32 max, int32 Key);

	UFUNCTION(BlueprintCallable, Category = "DunGen|Randomizer")
		static bool RandomizeFromChance(ERandomizerEnum Randomizer, int32 chance, int32 Key);
	
};
