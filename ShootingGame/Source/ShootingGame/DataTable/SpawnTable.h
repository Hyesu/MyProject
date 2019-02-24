#pragma once
#include "DataTable.h"
#include <map>

using SpawnWeightType = unsigned int;
using SpawnWeightPairType = std::pair<FName, SpawnWeightType>; // <itemStrID, spawnWeight>
struct SpawnData : public Data
{
	std::vector<FName> includeTypes;
	std::vector<FName> excludeItems;
	std::map<FName, SpawnWeightType> weightOverrideItemMap;

	std::vector<SpawnWeightPairType> itemSpawnWeightList;
	SpawnWeightType totalWeight{ 0 };
};

class SpawnTable : public DataTable
{
	DECL_SINGLETONE(SpawnTable);

public:
	void Init() override;
	void PostInit() override;
	void Finalize() override;

	const SpawnData* GetData(const DataKey& key) override;
	const SpawnData* GetData(const FName& key) override;

private:
	using SubTypeWeightMap = std::map<FName, SpawnWeightType>; // <subType, spawnWeight>
	std::map < FName, std::pair<SpawnWeightType, SubTypeWeightMap>> _weightByType;

};

SpawnTable* GetSpawnTable();