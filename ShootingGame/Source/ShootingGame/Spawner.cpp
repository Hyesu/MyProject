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

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RANGE"));
	RootComponent = MeshComponent;
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
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, FTimerDelegate::CreateLambda([this]() {
		this->PreSpawn();

		int32 SpawnCount{ FMath::RandRange(this->GetMinCount(), this->GetMaxCount()) };
		for (int32 i = 0; i < SpawnCount; ++i)
		{
			this->Spawn();
		}
		this->PostSpawn();

	}), SpawnIntervalInSec, PeriodicSpawn);
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
	FVector TargetLocation{ GetActorLocation() };
	TargetLocation.X += FMath::RandRange(-SpawnRange, SpawnRange);
	TargetLocation.Y += FMath::RandRange(-SpawnRange, SpawnRange);

	auto NewFdObject = GetWorld()->SpawnActor<AFieldObject>(TargetLocation, FRotator::ZeroRotator);
	if (NewFdObject != nullptr)
	{
		const SpawnData* SData{ GetSpawnTable()->GetData(SpawnDataKey) };
		if (SData != nullptr)
		{
			int32 Weight{ FMath::RandRange(0, SData->TotalWeight) };
			int32 AccWeight{ 0 };
			auto It = std::find_if(SData->ItemSpawnWeightList.cbegin(), SData->ItemSpawnWeightList.cend(), [&AccWeight, Weight](const SpawnWeightPairType& SpawnWeightPair) {
				AccWeight += SpawnWeightPair.second;
				return Weight <= AccWeight;
			});
			if (It != SData->ItemSpawnWeightList.cend())
			{
				SG_LOG("SpawnItem: %s", *It->first.GetPlainNameString());

				// todo: data driven. mesh, scale, ...
			}
			else
			{
				SG_LOG("Spawn Logic Error: RandomValue[%d], AccValue[%d], SpawnKey[%s]", Weight, AccWeight, *SpawnDataKey.GetPlainNameString());
			}
		}
		else
		{
			SG_LOG("Spawn Data Null: %s", *SpawnDataKey.GetPlainNameString());
		}
	}
}