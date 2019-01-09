#pragma once
#include "DataTable.h"

using SpawnWeightType = unsigned int;
using SpawnWeightPairType = std::pair<FName, SpawnWeightType>;
struct SpawnData : public Data
{
	std::vector<SpawnWeightPairType> ItemSpawnWeightList;
	SpawnWeightType TotalWeight{ 0 };
};

class SpawnTable : public DataTable
{
	DECL_SINGLETONE(SpawnTable);

public:
	const SpawnData* GetData(const DataKey& Key) override;
	const SpawnData* GetData(const FName& Key) override;
	void Init();
};

SpawnTable* GetSpawnTable();