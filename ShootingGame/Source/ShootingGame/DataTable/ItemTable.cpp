#include "ItemTable.h"
#include "Paths.h"
#include "ShootingGame.h"
#include "../Utility/JsonUtil.h"

IMPL_SINGLETONE(ItemTable);

ItemTable* GetItemTable()
{
	return static_cast<ItemTable*>(ItemTable::GetInstance());
}

void ItemTable::Init()
{
	InitItems();
	InitWeapons();

	SG_LOG("ItemTable Init Success: size[%d]", _dataMap.size());
}

const ItemData* ItemTable::GetData(const DataKey& key)
{
	return static_cast<const ItemData*>(DataTable::GetData(key));
}

const ItemData* ItemTable::GetData(const FName& stringKey)
{
	return static_cast<const ItemData*>(DataTable::GetData(stringKey));
}

void ItemTable::PostInit()
{

}

void ItemTable::Finalize()
{
	DestroyInstance();
}

void ItemTable::InitItems()
{
	static FString dataTableFilePath{ FPaths::ProjectContentDir().Append(TEXT("Data/item.json")) };
	auto itemJsonUtil = std::make_unique<JsonUtil>();
	if (itemJsonUtil->Init(dataTableFilePath) != JsonUtil::Result::Success)
	{
		SG_ERROR("Json File Init Fail: %s", *dataTableFilePath);
		return;
	}

	itemJsonUtil->ForEachArray(itemJsonUtil->GetRootObject(), "ItemList", [utilPtr = itemJsonUtil.get(), this](const JsonObjectPtr& itemObject) {
		auto data = std::make_unique<ItemData>();
		DataKey key{ 0 };
		if (itemObject->TryGetNumberField("ID", key) == false)
		{
			SG_ERROR("Key must be exist: file[%s]", *dataTableFilePath);
			return false;
		}
		data->key = key;
		data->stringKey = *itemObject->GetStringField("StrID");

		itemObject->TryGetStringField("Name", data->name);
		utilPtr->GetNameField(itemObject, "Type", data->type);
		utilPtr->GetNameField(itemObject, "SubType", data->subType);
		utilPtr->GetVectorField(itemObject, "ScaleRatio", data->scale);
		itemObject->TryGetNumberField("SpawnWeight", data->spawnWeight);
		itemObject->TryGetStringField("Mesh", data->meshPath);

		AddData(key, std::move(data));
		return true;
	});
}

void ItemTable::InitWeapons()
{
	static FString dataTableFilePath{ FPaths::ProjectContentDir().Append(TEXT("Data/item_weapon.json")) };
	auto itemJsonUtil = std::make_unique<JsonUtil>();
	if (itemJsonUtil->Init(dataTableFilePath) != JsonUtil::Result::Success)
	{
		SG_ERROR("Json File Init Fail: %s", *dataTableFilePath);
		return;
	}

	itemJsonUtil->ForEachArray(itemJsonUtil->GetRootObject(), "ItemList", [utilPtr = itemJsonUtil.get(), this](const JsonObjectPtr& itemObject) {
		DataKey key{ 0 };
		if (itemObject->TryGetNumberField("ID", key) == false)
		{
			SG_ERROR("Key must be exist: file[%s]", *dataTableFilePath);
			return false;
		}
		
		auto it = _dataMap.find(key);
		if (it == _dataMap.end()) {
			SG_ERROR("Not exist item: weapon id[%d]", key);
			return false;
		}

		ItemData* data = static_cast<ItemData*>(it->second.get());
		auto weaponData = std::make_unique<WeaponData>(*data);
		utilPtr->GetNameField(itemObject, "Ammo", weaponData->ammo);
		_dataMap.erase(it);
		_dataMap.emplace(key, std::move(weaponData));
		return true;
	});
}