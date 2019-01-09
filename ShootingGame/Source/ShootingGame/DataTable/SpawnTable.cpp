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
	static FString DataTableFilePath{ FPaths::ProjectContentDir().Append(TEXT("Data/spawn.json")) };
	auto JsonUtility = std::make_unique<JsonUtil>();
	if (JsonUtility->Init(DataTableFilePath) != JsonUtil::Result::Success)
	{
		SG_LOG("Json File Init Fail: %s", *DataTableFilePath);
		return;
	}

	DataKey Key{ 0 };
	JsonUtility->ForEachArray(JsonUtility->GetRootObject(), "SpawnerList", [UtilPtr = JsonUtility.get(), this, &Key](const JsonObjectPtr& SpawnerObject) {
		auto SData = std::make_unique<SpawnData>();		
		SData->Key = Key++;
		SData->StringKey = *SpawnerObject->GetStringField("StrID");
		SData->ItemSpawnWeightList.clear();

		std::vector<FName> ExcludeItemList, IncludeTypeList;
		UtilPtr->GetNameListField(SpawnerObject, "ExcludeItem", ExcludeItemList);
		UtilPtr->GetNameListField(SpawnerObject, "TypeList", IncludeTypeList);

		// build spawn item list from item table
		GetItemTable()->ForEachData([&ExcludeItemList, &IncludeTypeList, ItemSpawnWeightList = &SData->ItemSpawnWeightList](const Data* ItemDataRaw) {
			const ItemData* Item{ static_cast<const ItemData*>(ItemDataRaw) };
			if (std::find(ExcludeItemList.cbegin(), ExcludeItemList.cend(), Item->StringKey) != ExcludeItemList.cend())
			{
				return;
			}

			if (std::find(IncludeTypeList.cbegin(), IncludeTypeList.cend(), Item->Type) == IncludeTypeList.cend())
			{
				return;
			}

			ItemSpawnWeightList->emplace_back(Item->StringKey, Item->SpawnWeight);
		});

		// override spawn weight
		const TArray<JsonValuePtr>& WeightOverrideArray{ SpawnerObject->GetArrayField("WeightOverride") };
		for (auto& WeightOverrideValuePtr : WeightOverrideArray)
		{
			const JsonObjectPtr& WeightOverrideObject{ WeightOverrideValuePtr->AsObject() };
			for (auto& It : WeightOverrideObject->Values)
			{
				auto SpawnWeightIter{ std::find_if(SData->ItemSpawnWeightList.begin(), SData->ItemSpawnWeightList.end(), [ItemStringKey = It.Key](const std::pair<FName, SpawnWeightType>& SpawnWeight) {
					return SpawnWeight.first == FName(*ItemStringKey);
				}) };

				if (SpawnWeightIter != SData->ItemSpawnWeightList.end())
				{
					SpawnWeightIter->second = It.Value->AsNumber();
				}
			}
		}

		AddData(Key, std::move(SData));
		return true;
	});

	JsonUtility->ForEachArray(JsonUtility->GetRootObject(), "WeightByType", [UtilPtr = JsonUtility.get(), this](const JsonObjectPtr& WeightObject) {
		SubTypeWeightMap& SubTypeMap{ AddWeightByType(*WeightObject->GetStringField("Type"), WeightObject->GetNumberField("Weight")) };
		UtilPtr->ForEachArray(WeightObject, "SubType", [&SubTypeMap](const JsonObjectPtr& SubTypeWeightObject) {
			SubTypeMap.emplace(*SubTypeWeightObject->GetStringField("Type"), SubTypeWeightObject->GetNumberField("Weight"));
			return true;
		});
		return true;
	});

	// calc total spawn weight
	for(auto It = DataMap.begin(); It != DataMap.end(); ++It)
	{
		SpawnData* SpawnDataRaw{ static_cast<SpawnData*>(It->second.get()) };
		SpawnWeightType TotalWeight{ 0 };

		std::for_each(SpawnDataRaw->ItemSpawnWeightList.begin(), SpawnDataRaw->ItemSpawnWeightList.end(), [&TotalWeight, this](SpawnWeightPairType& SpawnWeightPair) {
			const ItemData* Item{ GetItemTable()->GetData(SpawnWeightPair.first) };
			if (Item != nullptr)
			{
				SpawnWeightPair.second *= (GetWeightByType(Item->Type) * GetWeightBySubType(Item->Type, Item->SubType));
			}

			SG_LOG("Item[%s], Weight[%d]", *Item->Name, SpawnWeightPair.second);
			TotalWeight += SpawnWeightPair.second;
		});
		SpawnDataRaw->TotalWeight = TotalWeight;

	}
}

const SpawnData* SpawnTable::GetData(const DataKey& Key)
{
	return static_cast<const SpawnData*>(DataTable::GetData(Key));
}

const SpawnData* SpawnTable::GetData(const FName& StringKey)
{
	return static_cast<const SpawnData*>(DataTable::GetData(StringKey));
}

SubTypeWeightMap& SpawnTable::AddWeightByType(const FName& Type, SpawnWeightType Weight)
{
	WeightByTypeMap.emplace(Type, std::make_pair(Weight, SubTypeWeightMap()));
	return WeightByTypeMap[Type].second;
}

SpawnWeightType SpawnTable::GetWeightByType(const FName& Type)
{
	auto It = WeightByTypeMap.find(Type);
	return It != WeightByTypeMap.end() ? It->second.first : 1;
}

SpawnWeightType SpawnTable::GetWeightBySubType(const FName& Type, const FName& SubType)
{
	auto It = WeightByTypeMap.find(Type);
	if (It == WeightByTypeMap.end())
		return 1;

	auto SubIt = It->second.second.find(SubType);
	return SubIt != It->second.second.end() ? SubIt->second : 1;
}