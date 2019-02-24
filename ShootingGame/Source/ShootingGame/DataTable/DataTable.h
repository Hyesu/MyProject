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

	virtual void Init() = 0;
	virtual void PostInit() = 0;
	virtual void Finalize() = 0;

protected:
	std::unordered_map<DataKey, std::unique_ptr<struct Data>> _dataMap;	
	TMap<FName, DataKey> _keyIndexMap;
};

class DataManager
{
	DECL_SINGLETONE(DataManager);

public:
	void Init();
	void Finalize();

private:
	void DoInit();

	std::list<DataTable*> _tables;
};

DataManager* GetDataManager();