#pragma once
#include "DataTable.h"

struct ItemData : public Data
{
	FName Type;
	FName SubType;
	FString Name;
	FVector Scale;
	unsigned int SpawnWeight{ 0 };
};

class ItemTable : public DataTable
{
public:
	const ItemData* GetData(const DataKey& Key) override;
	void Init();
};

ItemTable* GetItemTable();