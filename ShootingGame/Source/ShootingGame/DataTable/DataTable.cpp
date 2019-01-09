#include "DataTable.h"
#include <algorithm>

const Data* DataTable::GetData(const DataKey& Key)
{
	auto It = DataMap.find(Key);
	if (It != DataMap.end())
		return It->second.get();

	return nullptr;
}

const Data* DataTable::GetData(const FName& StringKey)
{
	DataKey* NumberKey{ KeyIndexMap.Find(StringKey) };
	if (NumberKey == nullptr)
		return nullptr;

	return GetData(*NumberKey);
}

void DataTable::AddData(DataKey Key, DataPtr&& Data)
{
	KeyIndexMap.Emplace(Data->StringKey, Key);
	DataMap.emplace(Key, std::move(Data));
}

void DataTable::ForEachData(const DataIterateFunc& ForEachFunc)
{
	for (auto It = DataMap.begin(); It != DataMap.end(); ++It)
	{
		ForEachFunc(It->second.get());
	}
}