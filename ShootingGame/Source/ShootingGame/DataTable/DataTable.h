#pragma once
#include "Singleton.h"
#include <memory>
#include <unordered_map>

using DataKey = unsigned int;
struct Data
{
	DataKey key{ 0 };
};

class DataTable
{
	DECL_SINGLETONE(DataTable);

public:
	virtual const Data* GetData(const DataKey& key);

private:
	std::unordered_map<DataKey, std::unique_ptr<struct Data>> m_data;
};