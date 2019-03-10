#include "SpawnTable.h"
#include "ItemTable.h"
#include "Paths.h"
#include "ShootingGame.h"
#include "../Utility/JsonUtil.h"
#include "DefaultValueHelper.h"
#include <algorithm>

IMPL_SINGLETONE(SpawnTable);

SpawnTable* GetSpawnTable()
{
	return static_cast<SpawnTable*>(SpawnTable::GetInstance());
}

void SpawnTable::Init()
{
	InitSpawnWeight();
	InitSpawnRule();
}

const SpawnData* SpawnTable::GetData(const DataKey& key)
{
	return static_cast<const SpawnData*>(DataTable::GetData(key));
}

const SpawnData* SpawnTable::GetData(const FName& stringKey)
{
	return static_cast<const SpawnData*>(DataTable::GetData(stringKey));
}

void SpawnTable::PostInit()
{
	for (auto& it : _dataMap) {
		SpawnData* spawnData = static_cast<SpawnData*>(it.second.get());		
		GetItemTable()->ForEachData([spawnData](const Data* d) {
			const ItemData* itemData{ static_cast<const ItemData*>(d) };
			// check include type
			{
				auto it = std::find(spawnData->includeTypes.cbegin(), spawnData->includeTypes.cend(), itemData->type);
				if (it == spawnData->includeTypes.cend()) {
					return;
				}
			}

			// check exclude item
			{
				auto it = std::find(spawnData->excludeItems.cbegin(), spawnData->excludeItems.cend(), itemData->stringKey);
				if (it != spawnData->excludeItems.cend()) {
					return;
				}
			}

			auto overrideIter = spawnData->weightOverrideItemMap.find(itemData->stringKey);
			SpawnWeightType weight = overrideIter != spawnData->weightOverrideItemMap.end() ? overrideIter->second : itemData->spawnWeight;
			spawnData->itemSpawnWeightList.emplace_back(itemData->stringKey, weight);
			spawnData->totalWeight += weight;
		});
	}
}

void SpawnTable::Finalize()
{
	DestroyInstance();
}

void SpawnTable::InitSpawnWeight()
{
	static FString dataTableFilePath{ FPaths::ProjectContentDir().Append(TEXT("Data/spawn.json")) };
	auto spawnerFile = std::make_unique<JsonUtil>();
	if (spawnerFile->Init(dataTableFilePath) != JsonUtil::Result::Success) {
		SG_ERROR("Json File Init Fail: %s", *dataTableFilePath);
		return;
	}

	DataKey key{ 0 };
	spawnerFile->ForEachArray(spawnerFile->GetRootObject(), "SpawnerList", [utilPtr = spawnerFile.get(), this, &key](const JsonObjectPtr& spawnerObject) {
		auto spawnData = std::make_unique<SpawnData>();
		spawnData->key = key++;
		spawnData->stringKey = *spawnerObject->GetStringField("StrID");
		spawnData->itemSpawnWeightList.clear();
		utilPtr->GetNameListField(spawnerObject, "ExcludeItem", spawnData->excludeItems);
		utilPtr->GetNameListField(spawnerObject, "TypeList", spawnData->includeTypes);

		utilPtr->ForEachArray(spawnerObject, "WeightOverride", [data = spawnData.get()](const JsonObjectPtr& overrideItemObject) {
			for (auto& it : overrideItemObject->Values) {
				SpawnWeightType overrideWeight = 0;
				if (it.Value->TryGetNumber(overrideWeight) == true) {
					data->weightOverrideItemMap.emplace(*it.Key, overrideWeight);
				}
				else {
					SG_ERROR("Spawn Data Error: spawner[%s] override item[%s] cannot cast number!", *data->stringKey.ToString(), *it.Key);
					return false;
				}
			}
			return true;
		});

		AddData(key, std::move(spawnData));
		return true;
	});

	spawnerFile->ForEachArray(spawnerFile->GetRootObject(), "WeightByType", [utilPtr = spawnerFile.get(), this](const JsonObjectPtr& data) {
		auto& weightByType = _weightByType[*data->GetStringField("Type")];
		data->TryGetNumberField("Weight", weightByType.first);

		const JsonObjectPtr& subTypes = data->GetObjectField("SubType");
		for (auto& it : subTypes->Values) {
			SpawnWeightType subTypeWeight = 0;
			it.Value->TryGetNumber(subTypeWeight);
			weightByType.second.emplace(*it.Key, subTypeWeight);
		}
		return true;
	});
}

void SpawnTable::InitSpawnRule()
{
	static FString dataTableFilePath{ FPaths::ProjectContentDir().Append(TEXT("Data/spawn_rule.json")) };
	auto spawnerFile = std::make_unique<JsonUtil>();
	if (spawnerFile->Init(dataTableFilePath) != JsonUtil::Result::Success) {
		SG_ERROR("Json File Init Fail: %s", *dataTableFilePath);
		return;
	}

	spawnerFile->ForEachArray(spawnerFile->GetRootObject(), "BonusSpawnRuleList", [utilPtr = spawnerFile.get(), this](const JsonObjectPtr& jsonObject) {
		FName bonusType;
		utilPtr->GetNameField(jsonObject, "SpawnedItemType", bonusType);
		auto bonusSpawnData{ std::make_unique<BonusSpawnData>() };
		utilPtr->GetNameField(jsonObject, "BonusItemReference", bonusSpawnData->hint);

		const JsonObjectPtr& countRatio = jsonObject->GetObjectField("CountRatios");
		for (auto& it : countRatio->Values) {
			int32 count = 0;
			if (FDefaultValueHelper::ParseInt(it.Key, count) == false) {
				SG_ERROR("BonusSpawnRuleList CountRatios key must can be parsed to integer: value[%s]", *it.Key);
				return false;
			}
			uint32 ratio = it.Value->AsNumber();
			bonusSpawnData->totalRatio += ratio;
			bonusSpawnData->bonusCountList.emplace_back(count, ratio);
		}

		_bonusSpawnRule.emplace(bonusType, std::move(bonusSpawnData));
		return true;
	});
}

const BonusSpawnData* SpawnTable::GetBonusData(const FName& type)
{
	auto it = _bonusSpawnRule.find(type);
	if (it == _bonusSpawnRule.end()) {
		return nullptr;
	}
	return it->second.get();
}