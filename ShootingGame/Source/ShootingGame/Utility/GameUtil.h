#pragma once
#include <vector>

namespace GameUtil
{
	template<typename T>
	bool GetRandomResult(const std::vector<std::pair<T, uint32>>& candidates, uint32 totalRatio, T& result)
	{
		int32 weight{ FMath::RandRange(0, totalRatio) };
		int32 accWeight{ 0 };
		auto it = std::find_if(candidates.cbegin(), candidates.cend(), [&accWeight, weight](auto& spawnWeightPair) {
			accWeight += spawnWeightPair.second;
			return weight <= accWeight;
		});

		if (it == candidates.cend()) {
			return false;
		}

		result = it->first;
		return true;
	}
};