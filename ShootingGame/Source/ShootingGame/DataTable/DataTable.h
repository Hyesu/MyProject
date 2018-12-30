#pragma once
#include "Singleton.h"
#include "NameTypes.h"
#include "Vector.h"
#include <memory>
#include <unordered_map>

using DataKey = unsigned int;
struct Data
{
	DataKey Key{ 0 };
	FName StringKey;
};
using DataPtr = std::unique_ptr<Data>;

class DataTable
{
	DECL_SINGLETONE(DataTable);

public:
	virtual const Data* GetData(const DataKey& Key);
	void AddData(DataKey Key, DataPtr&& Data);
	unsigned int GetCount() const { return DataMap.size(); }

private:
	std::unordered_map<DataKey, std::unique_ptr<struct Data>> DataMap;	
	TMap<FName, DataKey> KeyIndexMap;
};