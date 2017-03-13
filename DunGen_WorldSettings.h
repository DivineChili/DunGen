// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Randomizer.h"

#include "GameFramework/WorldSettings.h"
#include "DunGen_WorldSettings.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ERandomizerEnum : uint8
{
	RE_Global	UMETA(DisplayName = "Global"),
	RE_Maze		UMETA(DisplayName = "Maze"),
	RE_Room		UMETA(DisplayName = "Room"),
	RE_Loot		UMETA(DisplayName = "Loot")
};

UCLASS()
class DUNGEN_API ADunGen_WorldSettings : public AWorldSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum")
		ERandomizerEnum RandomizerEnum;
};
