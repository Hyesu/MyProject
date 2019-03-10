#include "DataTable.h"
#include "ItemTable.h"
#include "SpawnTable.h"
#include "Paths.h"
#include "ShootingGame.h"
#include "Utility/JsonUtil.h"
#include <algorithm>

IMPL_SINGLETONE(DataManager);

const Data* DataTable::GetData(const DataKey& key)
{
	auto It = _dataMap.find(key);
	if (It != _dataMap.end())
		return It->second.get();

	return nullptr;
}

const Data* DataTable::GetData(const FName& stringKey)
{
	DataKey* numberKey{ _keyIndexMap.Find(stringKey) };
	if (numberKey == nullptr)
		return nullptr;

	return GetData(*numberKey);
}

void DataTable::AddData(DataKey key, DataPtr&& data)
{
	_keyIndexMap.Emplace(data->stringKey, key);
	_dataMap.emplace(key, std::move(data));
}

void DataTable::ForEachData(const DataIterateFunc& forEachFunc)
{
	for (auto It = _dataMap.begin(); It != _dataMap.end(); ++It)
	{
		forEachFunc(It->second.get());
	}
}

DataManager* GetDataManager()
{
	return DataManager::GetInstance();
}

void DataManager::Init()
{
#define REGISTER_TABLE(tableName) _tables.push_back(Get##tableName##Table())

	REGISTER_TABLE(Item);
	REGISTER_TABLE(Spawn);

	DoInit();
}

void DataManager::Finalize()
{
	std::for_each(_tables.begin(), _tables.end(), [](DataTable* table) {
		table->Finalize();
	});
}

void DataManager::DoInit()
{
	std::for_each(_tables.begin(), _tables.end(), [](DataTable* table) {
		table->Init();
	});

	std::for_each(_tables.begin(), _tables.end(), [](DataTable* table) {
		table->PostInit();
	});

	InitCharacterData();
}

void DataManager::InitCharacterData()
{
	static FString dataTableFilePath{ FPaths::ProjectContentDir().Append(TEXT("Data/character.json")) };
	auto jsonFile = std::make_unique<JsonUtil>();
	if (jsonFile->Init(dataTableFilePath) != JsonUtil::Result::Success) {
		SG_ERROR("Json File Init Fail: %s", *dataTableFilePath);
		return;
	}

	const JsonObjectPtr& charObject = jsonFile->GetRootObject()->GetObjectField("CharacterInfo");
	_charData = std::make_unique<CharacterData>();
	_charData->defaultCapacity = charObject->GetNumberField("DefaultCapacity");
	_charData->maxBoost = charObject->GetNumberField("BoostMax");
	_charData->maxHP = charObject->GetNumberField("HpMax");
	_charData->speedCrouch = charObject->GetNumberField("SpeedCrouch");
	_charData->speedFast = charObject->GetNumberField("SpeedFast");
	_charData->speedNormal = charObject->GetNumberField("SpeedNormal");
	_charData->speedSlow = charObject->GetNumberField("SpeedSlow");
	_charData->searchDistanceRadius = charObject->GetNumberField("ItemSearchDistance");
}