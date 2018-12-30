#include "DataTable.h"

IMPL_SINGLETONE(DataTable);

const Data* DataTable::GetData(const DataKey& Key)
{
	auto it = DataMap.find(Key);
	if (it != DataMap.end())
		return it->second.get();

	return nullptr;
}

void DataTable::AddData(DataKey Key, DataPtr&& Data)
{
	KeyIndexMap.Emplace(Data->StringKey, Key);
	DataMap.emplace(Key, std::move(Data));
}