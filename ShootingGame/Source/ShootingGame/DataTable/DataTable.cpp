#include "DataTable.h"
#include <algorithm>

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