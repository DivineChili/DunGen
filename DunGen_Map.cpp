// Fill out your copyright notice in the Description page of Project Settings.

#include "DunGen.h"
#include "DunGen_WorldSettings.h"

#include "Algorithms.h"
#include "DunGen_Map.h"
#include "Cell.h"
#include "Cell_Map.h"

#include <vector>


Randomizer ADunGen_Map::GlobalRandomizer = Randomizer(0);
Randomizer ADunGen_Map::MazeRandomizer = Randomizer(1);
Randomizer ADunGen_Map::RoomRandomizer = Randomizer(2);
Randomizer ADunGen_Map::LootRandomizer = Randomizer(3);

Cell_Map ADunGen_Map::grid = Cell_Map();

// Sets default values
ADunGen_Map::ADunGen_Map()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(10.0f);
	

	// VIsual Representation of Actor
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Sphere"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
		SphereVisual->SetHiddenInGame(true);
	}

	MazeWalls = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ISM"));
	MazeWalls->SetupAttachment(RootComponent);


	MazeFloor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	MazeFloor->SetupAttachment(RootComponent);

	
	// Get Assets and initialize options
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MazeMaterial(TEXT("/Game/Game/Material/M_MazeWall.M_MazeWall"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FloorMaterial(TEXT("/Game/Game/Material/M_MazeFloor.M_MazeFloor"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MazeCube(TEXT("/Game/Game/Mesh/Cube.Cube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MazePlane(TEXT("/Game/Game/Mesh/Plane.Plane"));

	if (MazeMaterial.Succeeded() && FloorMaterial.Succeeded() && MazeCube.Succeeded() && MazePlane.Succeeded()) {
		// WallsComponent settings
		this->MazeWalls->SetStaticMesh(MazeCube.Object);
		this->MazeWalls->SetMaterial(0, MazeMaterial.Object);

		// FloorComponent Settings
		this->MazeFloor->SetStaticMesh(MazePlane.Object);
		this->MazeFloor->SetMaterial(0, FloorMaterial.Object);
	}
}

// Called when the game starts or when spawned
void ADunGen_Map::BeginPlay()
{
	Super::BeginPlay();


	if (!UseRandomSeed) {
		ADunGen_Map::GlobalRandomizer.setSeed(FCString::Atoi(*Seed));
	}
	else {
		ADunGen_Map::GlobalRandomizer.setSeed(rand() % 999999);
	}

	ADunGen_Map::MazeRandomizer.setSeed(ADunGen_Map::GlobalRandomizer.randomizeFromKey(0));
	ADunGen_Map::RoomRandomizer.setSeed(ADunGen_Map::GlobalRandomizer.randomizeFromKey(1));
	ADunGen_Map::LootRandomizer.setSeed(ADunGen_Map::GlobalRandomizer.randomizeFromKey(2));

	// Create the Instance thing ...

	// Create the maze
	ADunGen_Map::grid = Cell_Map(this->SizeX, this->SizeY);

	int start_pos[2] = { this->StartPositionX,this->StartPositionY };

	Algorithms::recursive_backtracking(start_pos, &ADunGen_Map::grid, ADunGen_Map::MazeRandomizer);


	FTransform trans;

	trans.SetScale3D(FVector(1 * MapScaleRate, 1 * MapScaleRate, WallHeight * MapScaleRate));

	// Make instances, and construct maze here!

	// Loop Through each cell
	for (int maze_x = 0; maze_x < this->SizeX; maze_x++) {
		for (int maze_y = 0; maze_y < this->SizeY; maze_y++)
		{
			// Loop through all characters in cell
			for (int cell_x = 0; cell_x < 5; cell_x++) {
				for (int cell_y = 0; cell_y < 5; cell_y++) {
					Cell *tempCell = ADunGen_Map::grid.getCellAtPos(maze_x, maze_y);
					if (tempCell->getCharAtPos(cell_x, cell_y) == '#')
					{
						trans.SetLocation(FVector(maze_x * 500 * MapScaleRate + cell_x * 100 * MapScaleRate, maze_y * 500 * MapScaleRate + cell_y * 100 * MapScaleRate, 0));
						MazeWalls->AddInstance(trans);
					}
				}
			}
		}
	}
	trans.SetScale3D(FVector(this->SizeX * 5 * MapScaleRate, this->SizeY * 5 * MapScaleRate, 0));
	trans.SetLocation(FVector((this->SizeX * 500 * MapScaleRate) / 2, (this->SizeY * 500 * MapScaleRate) / 2, -.01f));
	MazeFloor->SetRelativeTransform(trans);
}


// Called every frame
void ADunGen_Map::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ADunGen_Map::IsWall_Implementation(int GridX, int GridY, int CellX, int CellY) {
	return ADunGen_Map::grid.getCellAtPos(GridX, GridY)->getCharAtPos(CellX, CellY) == '#';
}

FString ADunGen_Map::GetOpenedSidesInCell_Implementation(int GridX, int GridY) {
	FString temp_string = "";
	for (int i = 0; i < 4; i++) {
		temp_string += ADunGen_Map::grid.getCellAtPos(GridX, GridY)->opened_sides[i] + " : ";
	}
	return temp_string;
}