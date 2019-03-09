// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "ShootingGame.h"
#include "ShootingGameGameMode.h"
#include "FieldObject/FieldItem.h"
#include "DataTable/SpawnTable.h"
#include "DataTable/ItemTable.h"
#include "Manager/WorldManager.h"
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
		PreSpawn();

		int32 spawnCount{ FMath::RandRange(_minCount, _maxCount) };
		for (int32 i = 0; i < spawnCount; ++i) {
			Spawn();
		}

		PostSpawn();

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
	// weapon with ammo
	for (auto& it : _spawnedItems) {
		const ItemData* itemData{ GetItemTable()->GetData(it.Key) };
		if (itemData->GetType() != ItemType::Weapon) {
			continue;
		}

		const WeaponData* weaponData{ static_cast<const WeaponData*>(itemData) };
		const ItemData* ammoData{ GetItemTable()->GetData(weaponData->ammo) };
		if (ammoData == nullptr) {
			continue;
		}

		auto newFdObject = GetWorld()->SpawnActor<AFieldItem>(GetSpawnLocation(), FRotator::ZeroRotator);
		if (newFdObject == nullptr) {
			SG_ERROR("Ammo Spawn fail: key[%s], ammo[%s]", *_spawnDataKey.ToString(), *ammoData->stringKey.ToString());
			return;
		}
		newFdObject->DataStringKey = ammoData->stringKey;
		WORLD_MGR->AddFieldObject(newFdObject);

		SG_LOG("Spawn Ammo: [%s]", *ammoData->stringKey.ToString());
		newFdObject->SetModelData(ammoData->meshPath, ammoData->scale);
	}
}

void ASpawner::Spawn()
{
	auto newFdObject = GetWorld()->SpawnActor<AFieldItem>(GetSpawnLocation(), FRotator::ZeroRotator);
	if (newFdObject == nullptr) {
		SG_ERROR("Spawn fail: key[%s]", *_spawnDataKey.ToString());
		return;
	}	
	WORLD_MGR->AddFieldObject(newFdObject);

	const SpawnData* spawnData{ GetSpawnTable()->GetData(_spawnDataKey) };
	if (spawnData == nullptr) {
		SG_ERROR("Spawn data is null: key[%s]", *_spawnDataKey.ToString());
		return;
	}

	int32 weight{ FMath::RandRange(0, spawnData->totalWeight) };
	int32 accWeight{ 0 };
	auto it = std::find_if(spawnData->itemSpawnWeightList.cbegin(), spawnData->itemSpawnWeightList.cend(), [&accWeight, weight](const SpawnWeightPairType& spawnWeightPair) {
		accWeight += spawnWeightPair.second;
		return weight <= accWeight;
	});

	if (it == spawnData->itemSpawnWeightList.cend()) {
		SG_ERROR("Spawn Logic Error: RandomValue[%d], AccValue[%d], SpawnKey[%s]", weight, accWeight, *_spawnDataKey.ToString());
		return;
	}

	SG_LOG("Spawn Item: [%s]", *it->first.ToString());

	const ItemData* itemData{ GetItemTable()->GetData(it->first) };
	if (itemData == nullptr) {
		SG_ERROR("Spawn Item is null: spawner[%s], item[%s]", *_spawnDataKey.ToString(), *it->first.ToString());
		return;
	}

	_spawnedItems.Emplace(itemData->key, newFdObject);
	newFdObject->DataStringKey = itemData->stringKey;
	newFdObject->SetModelData(itemData->meshPath, itemData->scale);
}

FVector ASpawner::GetSpawnLocation() const
{
	FVector targetLocation{ GetActorLocation() };
	targetLocation.X += FMath::RandRange(-_spawnRange, _spawnRange);
	targetLocation.Y += FMath::RandRange(-_spawnRange, _spawnRange);
	return targetLocation;
}