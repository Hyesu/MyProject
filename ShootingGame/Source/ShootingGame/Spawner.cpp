// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "ShootingGame.h"
#include "FieldObject.h"
#include "DataTable/SpawnTable.h"
#include <algorithm>

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RANGE"));
	RootComponent = _meshComponent;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::Init()
{
	GetWorld()->GetTimerManager().SetTimer(_spawnTimerHandle, FTimerDelegate::CreateLambda([this]() {
		this->PreSpawn();

		int32 spawnCount{ FMath::RandRange(this->GetMinCount(), this->GetMaxCount()) };
		for (int32 i = 0; i < spawnCount; ++i)
		{
			this->Spawn();
		}
		this->PostSpawn();

	}), _spawnIntervalInSec, _periodicSpawn);
}

void ASpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Init();
}

void ASpawner::PreSpawn()
{

}

void ASpawner::PostSpawn()
{

}

void ASpawner::Spawn()
{
	FVector targetLocation{ GetActorLocation() };
	targetLocation.X += FMath::RandRange(-_spawnRange, _spawnRange);
	targetLocation.Y += FMath::RandRange(-_spawnRange, _spawnRange);

	auto newFdObject = GetWorld()->SpawnActor<AFieldObject>(targetLocation, FRotator::ZeroRotator);
	if (newFdObject != nullptr)
	{
		const SpawnData* spawnData{ GetSpawnTable()->GetData(_spawnDataKey) };
		if (spawnData != nullptr)
		{
			int32 weight{ FMath::RandRange(0, spawnData->totalWeight) };
			int32 accWeight{ 0 };
			auto it = std::find_if(spawnData->itemSpawnWeightList.cbegin(), spawnData->itemSpawnWeightList.cend(), [&accWeight, weight](const SpawnWeightPairType& spawnWeightPair) {
				accWeight += spawnWeightPair.second;
				return weight <= accWeight;
			});

			if (it != spawnData->itemSpawnWeightList.cend())
			{
				SG_LOG("SpawnItem: %s", *it->first.GetPlainNameString());

				// todo: data driven. mesh, scale, ...
			}
			else
			{
				SG_LOG("Spawn Logic Error: RandomValue[%d], AccValue[%d], SpawnKey[%s]", weight, accWeight, *_spawnDataKey.GetPlainNameString());
			}
		}
		else
		{
			SG_LOG("Spawn Data Null: %s", *_spawnDataKey.GetPlainNameString());
		}
	}
}