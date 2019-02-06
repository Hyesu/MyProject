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
	DataKey key{ 0 };
	FName stringKey;
};
using DataPtr = std::unique_ptr<Data>;
using DataPair = std::pair<DataKey, DataPtr>;
using DataIterateFunc = std::function<void(const Data*)>;

class DataTable
{
public:
	virtual ~DataTable() {}
	virtual const Data* GetData(const DataKey& key);
	virtual const Data* GetData(const FName& stringKey);

	void AddData(DataKey key, DataPtr&& data);
	unsigned int GetCount() const { return _dataMap.size(); }
	void ForEachData(const DataIterateFunc& forEachFunc);

protected:
	std::unordered_map<DataKey, std::unique_ptr<struct Data>> _dataMap;	
	TMap<FName, DataKey> _keyIndexMap;
};