#pragma once
#include "Singleton.h"
#include "DataTable.h"

struct ItemData : public Data
{
	FName type;
	FName subType;
	FString name;
	FVector scale;
	unsigned int spawnWeight{ 0 };
};

class ItemTable : public DataTable
{
	DECL_SINGLETONE(ItemTable);

public:
	void Init() override;
	void PostInit() override;
	void Finalize() override;

	const ItemData* GetData(const DataKey& key) override;
	const ItemData* GetData(const FName& stringKey) override;
};

ItemTable* GetItemTable();