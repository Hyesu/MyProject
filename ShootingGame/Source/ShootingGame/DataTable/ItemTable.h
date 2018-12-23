#pragma once
#include "DataTable.h"

struct ItemData : public Data
{

};

class ItemTable : public DataTable
{
public:
	const ItemData* GetData(const DataKey& key) override;
	void Init();
};

ItemTable* GetItemTable();