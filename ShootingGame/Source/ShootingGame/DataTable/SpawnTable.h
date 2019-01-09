#pragma once
#include "DataTable.h"
#include <map>

using SpawnWeightType = unsigned int;
using SpawnWeightPairType = std::pair<FName, SpawnWeightType>;
using SubTypeWeightMap = std::map<FName, SpawnWeightType>;
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

	SubTypeWeightMap& AddWeightByType(const FName& Type, SpawnWeightType Weight);
	SpawnWeightType GetWeightByType(const FName& Type);
	SpawnWeightType GetWeightBySubType(const FName& Type, const FName& SubType);

private:
	std::map<FName, std::pair<SpawnWeightType, SubTypeWeightMap>> WeightByTypeMap;
};

SpawnTable* GetSpawnTable();