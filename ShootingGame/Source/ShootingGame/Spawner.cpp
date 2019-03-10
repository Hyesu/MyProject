// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "ShootingGame.h"
#include "ShootingGameGameMode.h"
#include "FieldObject/FieldItem.h"
#include "DataTable/SpawnTable.h"
#include "DataTable/ItemTable.h"
#include "Manager/WorldManager.h"
#include "Utility/GameUtil.h"
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
	for (auto& it : _spawnedItems) {
		const ItemData* itemData{ GetItemTable()->GetData(it.Key) };
		const BonusSpawnData* bonusSpawnData{ GetSpawnTable()->GetBonusData(itemData->type) };
		if (bonusSpawnData == nullptr) {
			continue;
		}

		const FName* bonusItemKey{ ItemData::GetNameField(itemData, bonusSpawnData->hint) };
		if (bonusItemKey == nullptr) {
			continue;
		}
		
		const ItemData* bonusItemData{ GetItemTable()->GetData(*bonusItemKey) };
		if (bonusItemData == nullptr) {
			continue;
		}

		uint32 bonusSpawnCount = 0;
		if (GameUtil::GetRandomResult(bonusSpawnData->bonusCountList, bonusSpawnData->totalRatio, bonusSpawnCount) == false) {
			continue;
		}

		for (uint32 i = 0; i < bonusSpawnCount; ++i) {
			auto newFdObject = GetWorld()->SpawnActor<AFieldItem>(GetSpawnLocation(), FRotator::ZeroRotator);
			if (newFdObject == nullptr) {
				SG_ERROR("Ammo Spawn fail: key[%s], ammo[%s]", *_spawnDataKey.ToString(), *bonusItemData->stringKey.ToString());
				return;
			}
			newFdObject->DataStringKey = bonusItemData->stringKey;
			WORLD_MGR->AddFieldObject(newFdObject);

			SG_LOG("Spawn Ammo: [%s]", *bonusItemData->stringKey.ToString());
			newFdObject->SetModelData(bonusItemData->meshPath, bonusItemData->scale);
		}
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

	FName resultItemStringKey;
	if (GameUtil::GetRandomResult(spawnData->itemSpawnWeightList, spawnData->totalWeight, resultItemStringKey) == false) {
		SG_ERROR("Spawn Item is null: spawner[%s]", *_spawnDataKey.ToString());
		return;
	}

	const ItemData* itemData{ GetItemTable()->GetData(resultItemStringKey) };
	if (itemData == nullptr) {
		SG_ERROR("Spawn Item is null: spawner[%s], item[%s]", *_spawnDataKey.ToString(), *resultItemStringKey.ToString());
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