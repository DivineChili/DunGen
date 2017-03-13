// Fill out your copyright notice in the Description page of Project Settings.

#include "DunGen.h"
#include "DunGen_Utilities.h"
#include "Randomizer.h"
#include "DunGen_Map.h"

bool UDunGen_Utilities::SetRandomizerSeed(ERandomizerEnum Randomizer, int seed)
{
	switch (Randomizer) {
	case ERandomizerEnum::RE_Global:
		ADunGen_Map::GlobalRandomizer.setSeed(seed);
		return true;
		break;
	case ERandomizerEnum::RE_Maze:
		ADunGen_Map::MazeRandomizer.setSeed(seed);
		return true;
		break;
	case ERandomizerEnum::RE_Room:
		ADunGen_Map::RoomRandomizer.setSeed(seed);
		return true;
		break;
	case ERandomizerEnum::RE_Loot:
		ADunGen_Map::LootRandomizer.setSeed(seed);
		return true;
		break;
	default:
		return false;
		break;
	}
}

int32 UDunGen_Utilities::GetRandomizerSeed(ERandomizerEnum Randomizer)
{
	switch (Randomizer)
	{
	case ERandomizerEnum::RE_Global:
		return ADunGen_Map::GlobalRandomizer.getSeed();
		break;
	case ERandomizerEnum::RE_Maze:
		return ADunGen_Map::MazeRandomizer.getSeed();
		break;
	case ERandomizerEnum::RE_Room:
		return ADunGen_Map::RoomRandomizer.getSeed();
		break;
	case ERandomizerEnum::RE_Loot:
		return ADunGen_Map::LootRandomizer.getSeed();
		break;
	default:
		return 0;
		break;
	}
}

int32 UDunGen_Utilities::RandomizeAtPosition(ERandomizerEnum Randomizer, int32 PositionX, int32 PositionY)
{
	switch (Randomizer)
	{
	case ERandomizerEnum::RE_Global:
		return ADunGen_Map::GlobalRandomizer.randomizeAtPos(PositionX, PositionY);
		break;
	case ERandomizerEnum::RE_Maze:
		return ADunGen_Map::MazeRandomizer.randomizeAtPos(PositionX, PositionY);
		break;
	case ERandomizerEnum::RE_Room:
		return ADunGen_Map::RoomRandomizer.randomizeAtPos(PositionX, PositionY);
		break;
	case ERandomizerEnum::RE_Loot:
		return ADunGen_Map::LootRandomizer.randomizeAtPos(PositionX, PositionY);
		break;
	default:
		return 0;
		break;
	}
}

int32 UDunGen_Utilities::RandomizeFromKey(ERandomizerEnum Randomizer, int32 Key) {
	switch (Randomizer)
	{
	case ERandomizerEnum::RE_Global:
		return ADunGen_Map::GlobalRandomizer.randomizeFromKey(Key);
		break;
	case ERandomizerEnum::RE_Maze:
		return ADunGen_Map::MazeRandomizer.randomizeFromKey(Key);
		break;
	case ERandomizerEnum::RE_Room:
		return ADunGen_Map::RoomRandomizer.randomizeFromKey(Key);
		break;
	case ERandomizerEnum::RE_Loot:
		return ADunGen_Map::LootRandomizer.randomizeFromKey(Key);
		break;
	default:
		return 0;
		break;
	}
}

int32 UDunGen_Utilities::RandomizeInRange(ERandomizerEnum Randomizer, int32 min, int32 max, int32 Key) {
	switch (Randomizer)
	{
	case ERandomizerEnum::RE_Global:
		return ADunGen_Map::GlobalRandomizer.randomizeInRange(min, max, Key);
		break;
	case ERandomizerEnum::RE_Maze:
		return ADunGen_Map::MazeRandomizer.randomizeInRange(min, max, Key);
		break;
	case ERandomizerEnum::RE_Room:
		return ADunGen_Map::RoomRandomizer.randomizeInRange(min, max, Key);
		break;
	case ERandomizerEnum::RE_Loot:
		return ADunGen_Map::LootRandomizer.randomizeInRange(min, max, Key);
		break;
	default:
		return 0;
		break;
	}
}

bool UDunGen_Utilities::RandomizeFromChance(ERandomizerEnum Randomizer, int32 chance, int32 Key) {
	switch (Randomizer)
	{
	case ERandomizerEnum::RE_Global:
		return (ADunGen_Map::GlobalRandomizer.randomizeFromChance(chance, Key) == 1) ? true : false;
		break;
	case ERandomizerEnum::RE_Maze:
		return (ADunGen_Map::MazeRandomizer.randomizeFromChance(chance, Key) == 1) ? true : false;
		break;
	case ERandomizerEnum::RE_Room:
		return (ADunGen_Map::RoomRandomizer.randomizeFromChance(chance, Key) == 1) ? true : false;
		break;
	case ERandomizerEnum::RE_Loot:
		return (ADunGen_Map::LootRandomizer.randomizeFromChance(chance, Key) == 1) ? true : false;
		break;
	default:
		return true;
		break;
	}
}