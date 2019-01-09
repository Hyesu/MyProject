#pragma once
#include "Singleton.h"
#include "NameTypes.h"
#include "Vector.h"
#include <memory>
#include <unordered_map>
#include <functional>

using DataKey = unsigned int;
struct Data
{
	DataKey Key{ 0 };
	FName StringKey;
};
using DataPtr = std::unique_ptr<Data>;
using DataPair = std::pair<DataKey, DataPtr>;
using DataIterateFunc = std::function<void(const Data*)>;

class DataTable
{
public:
	virtual const Data* GetData(const DataKey& Key);
	virtual const Data* GetData(const FName& StringKey);

	void AddData(DataKey Key, DataPtr&& Data);
	unsigned int GetCount() const { return DataMap.size(); }
	void ForEachData(const DataIterateFunc& ForEachFunc);

protected:
	std::unordered_map<DataKey, std::unique_ptr<struct Data>> DataMap;	
	TMap<FName, DataKey> KeyIndexMap;
};