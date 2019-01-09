#pragma once
#include "Singleton.h"
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
	DECL_SINGLETONE(ItemTable);

public:
	const ItemData* GetData(const DataKey& Key) override;
	const ItemData* GetData(const FName& StringKey) override;
	void Init();
};

ItemTable* GetItemTable();