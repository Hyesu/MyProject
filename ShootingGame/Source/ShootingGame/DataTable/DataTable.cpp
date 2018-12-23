#include "DataTable.h"

IMPL_SINGLETONE(DataTable);

const Data* DataTable::GetData(const DataKey& key)
{
	auto it = m_data.find(key);
	if (it != m_data.end())
		return it->second.get();

	return nullptr;
}