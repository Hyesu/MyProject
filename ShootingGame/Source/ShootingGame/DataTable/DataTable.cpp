#include "DataTable.h"
#include "ItemTable.h"
#include "SpawnTable.h"
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
}