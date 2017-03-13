// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Randomizer.h"
#include "MazeInteractable.h"
#include "Cell_Map.h"

#include <vector>

#include "GameFramework/Actor.h"
#include "DunGen_Map.generated.h"



UCLASS()
class DUNGEN_API ADunGen_Map : public AActor, public IMazeInteractable
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent *ActorRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UInstancedStaticMeshComponent *MazeWalls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent *MazeFloor;

	/*
		EditProperties
	*/

	UPROPERTY(Category = "MapOptions", EditAnywhere)
		int SizeX = 25;
	UPROPERTY(Category = "MapOptions", EditAnywhere)
		int SizeY = 25;

	UPROPERTY(Category = "MapOptions", EditAnywhere)
		int WallHeight = 3;

	UPROPERTY(Category = "MapOptions", EditAnywhere)
		int StartPositionX = 3;
	UPROPERTY(Category = "MapOptions", EditAnywhere)
		int StartPositionY = 3;

	UPROPERTY(Category = "MapOptions", EditAnywhere)
		float MapScaleRate = 1;

	UPROPERTY(Category = "Randomizer", EditAnywhere, meta=(EditCondition="!UseRandomSeed"))
		FString Seed = FString("I am a seed");

	UPROPERTY(Category = "Randomizer", EditAnywhere)
		bool UseRandomSeed = false;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DunGen")
		bool IsWall(int GridX, int GridY, int CellX, int CellY);
		virtual bool IsWall_Implementation(int GridX, int GridY, int CellX, int CellY) override;
		
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DunGen|Map")
		FString GetOpenedSidesInCell(int GridX, int GridY);
		virtual FString GetOpenedSidesInCell_Implementation(int GridX, int GridY) override;

	static Randomizer GlobalRandomizer;
	static Randomizer MazeRandomizer;
	static Randomizer RoomRandomizer;
	static Randomizer LootRandomizer;

	static Cell_Map grid;
	
	// Sets default values for this actor's properties
	ADunGen_Map();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
