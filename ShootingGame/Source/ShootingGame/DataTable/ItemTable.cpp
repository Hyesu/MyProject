#include "ItemTable.h"

ItemTable* GetItemTable()
{
	return static_cast<ItemTable*>(ItemTable::GetInstance());
}

void ItemTable::Init()
{
	
}

const ItemData* ItemTable::GetData(const DataKey& key)
{
	const Data* data{ DataTable::GetData(key) };
	if (data == nullptr)
		return nullptr;

	return static_cast<const ItemData*>(data);
}