#include "SpawnTable.h"
#include "ItemTable.h"
#include "Paths.h"
#include "ShootingGame.h"
#include "../Utility/JsonUtil.h"
#include <algorithm>

IMPL_SINGLETONE(SpawnTable);

SpawnTable* GetSpawnTable()
{
	return static_cast<SpawnTable*>(SpawnTable::GetInstance());
}

void SpawnTable::Init()
{
	static FString dataTableFilePath{ FPaths::ProjectContentDir().Append(TEXT("Data/spawn.json")) };
	auto jsonUtility = std::make_unique<JsonUtil>();
	if (jsonUtility->Init(dataTableFilePath) != JsonUtil::Result::Success)
	{
		SG_LOG("Json File Init Fail: %s", *dataTableFilePath);
		return;
	}

	DataKey key{ 0 };
	jsonUtility->ForEachArray(jsonUtility->GetRootObject(), "SpawnerList", [utilPtr = jsonUtility.get(), this, &key](const JsonObjectPtr& spawnerObject) {
		auto spawnData = std::make_unique<SpawnData>();		
		spawnData->key = key++;
		spawnData->stringKey = *spawnerObject->GetStringField("StrID");
		spawnData->itemSpawnWeightList.clear();

		std::vector<FName> excludeItemList, includeTypeList;
		utilPtr->GetNameListField(spawnerObject, "ExcludeItem", excludeItemList);
		utilPtr->GetNameListField(spawnerObject, "TypeList", includeTypeList);

		// build spawn item list from item table
		GetItemTable()->ForEachData([&excludeItemList, &includeTypeList, itemSpawnWeightList = &spawnData->itemSpawnWeightList](const Data* itemDataRaw) {
			const ItemData* item{ static_cast<const ItemData*>(itemDataRaw) };
			if (std::find(excludeItemList.cbegin(), excludeItemList.cend(), item->stringKey) != excludeItemList.cend())
			{
				return;
			}

			if (std::find(includeTypeList.cbegin(), includeTypeList.cend(), item->type) == includeTypeList.cend())
			{
				return;
			}

			itemSpawnWeightList->emplace_back(item->stringKey, item->spawnWeight);
		});

		// override spawn weight
		const TArray<JsonValuePtr>& weightOverrideArray{ spawnerObject->GetArrayField("WeightOverride") };
		for (auto& weightOverrideValuePtr : weightOverrideArray)
		{
			const JsonObjectPtr& weightOverrideObject{ weightOverrideValuePtr->AsObject() };
			for (auto& it : weightOverrideObject->Values)
			{
				auto spawnWeightIter{ std::find_if(spawnData->itemSpawnWeightList.begin(), spawnData->itemSpawnWeightList.end(), [itemStringKey = it.Key](const std::pair<FName, SpawnWeightType>& spawnWeight) {
					return spawnWeight.first == FName(*itemStringKey);
				}) };

				if (spawnWeightIter != spawnData->itemSpawnWeightList.end())
				{
					spawnWeightIter->second = it.Value->AsNumber();
				}
			}
		}

		AddData(key, std::move(spawnData));
		return true;
	});

	jsonUtility->ForEachArray(jsonUtility->GetRootObject(), "WeightByType", [utilPtr = jsonUtility.get(), this](const JsonObjectPtr& weightObject) {
		SubTypeWeightMap& subTypeMap{ AddWeightByType(*weightObject->GetStringField("Type"), weightObject->GetNumberField("Weight")) };
		utilPtr->ForEachArray(weightObject, "SubType", [&subTypeMap](const JsonObjectPtr& subTypeWeightObject) {
			subTypeMap.emplace(*subTypeWeightObject->GetStringField("Type"), subTypeWeightObject->GetNumberField("Weight"));
			return true;
		});
		return true;
	});

	// calc total spawn weight
	for(auto it = _dataMap.begin(); it != _dataMap.end(); ++it)
	{
		SpawnData* spawnDataRaw{ static_cast<SpawnData*>(it->second.get()) };
		SpawnWeightType totalWeight{ 0 };

		std::for_each(spawnDataRaw->itemSpawnWeightList.begin(), spawnDataRaw->itemSpawnWeightList.end(), [&totalWeight, this](SpawnWeightPairType& spawnWeightPair) {
			const ItemData* item{ GetItemTable()->GetData(spawnWeightPair.first) };
			if (item != nullptr)
			{
				spawnWeightPair.second *= (GetWeightByType(item->type) * GetWeightBySubType(item->type, item->subType));
			}

			SG_LOG("Item[%s], Weight[%d]", *item->name, spawnWeightPair.second);
			totalWeight += spawnWeightPair.second;
		});
		spawnDataRaw->totalWeight = totalWeight;

	}
}

const SpawnData* SpawnTable::GetData(const DataKey& key)
{
	return static_cast<const SpawnData*>(DataTable::GetData(key));
}

const SpawnData* SpawnTable::GetData(const FName& stringKey)
{
	return static_cast<const SpawnData*>(DataTable::GetData(stringKey));
}

SubTypeWeightMap& SpawnTable::AddWeightByType(const FName& type, SpawnWeightType weight)
{
	_weightByTypeMap.emplace(type, std::make_pair(weight, SubTypeWeightMap()));
	return _weightByTypeMap[type].second;
}

SpawnWeightType SpawnTable::GetWeightByType(const FName& type)
{
	auto it = _weightByTypeMap.find(type);
	return it != _weightByTypeMap.end() ? it->second.first : 1;
}

SpawnWeightType SpawnTable::GetWeightBySubType(const FName& type, const FName& subType)
{
	auto it = _weightByTypeMap.find(type);
	if (it == _weightByTypeMap.end())
		return 1;

	auto subIt = it->second.second.find(subType);
	return subIt != it->second.second.end() ? subIt->second : 1;
}