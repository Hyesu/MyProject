#pragma once
#include "DataTable.h"
#include <map>

using SpawnWeightType = uint32;
using SpawnWeightPairType = std::pair<FName, SpawnWeightType>; // <itemStrID, spawnWeight>
struct SpawnData : public Data
{
	std::vector<FName> includeTypes;
	std::vector<FName> excludeItems;
	std::map<FName, SpawnWeightType> weightOverrideItemMap;

	std::vector<SpawnWeightPairType> itemSpawnWeightList;
	SpawnWeightType totalWeight{ 0 };
};

struct BonusSpawnData
{
	FName hint;
	uint32 totalRatio{ 0 };
	std::vector<std::pair<uint32, uint32>> bonusCountList;
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
	const BonusSpawnData* GetBonusData(const FName& type);

private:
	void InitSpawnWeight();
	void InitSpawnRule();

	using SubTypeWeightMap = std::map<FName, SpawnWeightType>; // <subType, spawnWeight>
	std::map<FName, std::pair<SpawnWeightType, SubTypeWeightMap>> _weightByType;	

	std::map<FName, std::unique_ptr<BonusSpawnData>> _bonusSpawnRule;
};

SpawnTable* GetSpawnTable();