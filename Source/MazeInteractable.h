// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MazeInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UMazeInteractable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class DUNGEN_API IMazeInteractable
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/*
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DunGen")
		FString GetCellStateAtPos(int CellPositionX, int CellPositionY, int IndexX, int IndexY);
	*/

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DunGen|Map")
		bool IsWall(int GridX, int GridY, int CellX, int CellY);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DunGen|Map")
		FString GetOpenedSidesInCell(int GridX, int GridY);
};
