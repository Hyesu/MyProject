#pragma once
#include "DataTable.h"
#include <map>

using SpawnWeightType = unsigned int;
using SpawnWeightPairType = std::pair<FName, SpawnWeightType>;
using SubTypeWeightMap = std::map<FName, SpawnWeightType>;
struct SpawnData : public Data
{
	std::vector<SpawnWeightPairType> itemSpawnWeightList;
	SpawnWeightType totalWeight{ 0 };
};

class SpawnTable : public DataTable
{
	DECL_SINGLETONE(SpawnTable);

public:
	const SpawnData* GetData(const DataKey& key) override;
	const SpawnData* GetData(const FName& key) override;
	void Init();

	SubTypeWeightMap& AddWeightByType(const FName& type, SpawnWeightType weight);
	SpawnWeightType GetWeightByType(const FName& type);
	SpawnWeightType GetWeightBySubType(const FName& type, const FName& subType);

private:
	std::map<FName, std::pair<SpawnWeightType, SubTypeWeightMap>> _weightByTypeMap;
};

SpawnTable* GetSpawnTable();