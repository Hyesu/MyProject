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
	static FString DataTableFilePath{ FPaths::ProjectContentDir().Append(TEXT("Data/item.json")) };
	auto ItemJsonUtil = std::make_unique<JsonUtil>();
	if (ItemJsonUtil->Init(DataTableFilePath) != JsonUtil::Result::Success)
	{
		SG_LOG("Json File Init Fail: %s", *DataTableFilePath);
		return;
	}

	ItemJsonUtil->ForEachArray(ItemJsonUtil->GetRootObject(), "ItemList", [UtilPtr = ItemJsonUtil.get(), this](const JsonObjectPtr& ItemObject) {
		auto Data = std::make_unique<ItemData>();
		DataKey Key{ 0 };
		if (ItemObject->TryGetNumberField("ID", Key) == false)
		{
			SG_LOG("Key must be exist: file[%s]", *DataTableFilePath);
			return false;
		}
		Data->Key = Key;
		Data->StringKey = *ItemObject->GetStringField("StrID");

		ItemObject->TryGetStringField("Name", Data->Name);
		UtilPtr->GetNameField(ItemObject, "Type", Data->Type);
		UtilPtr->GetNameField(ItemObject, "SubType", Data->SubType);
		UtilPtr->GetVectorField(ItemObject, "ScaleRatio", Data->Scale);
		ItemObject->TryGetNumberField("SpawnWeight", Data->SpawnWeight);

		AddData(Key, std::move(Data));
		return true;
	});
}

const ItemData* ItemTable::GetData(const DataKey& Key)
{
	return static_cast<const ItemData*>(DataTable::GetData(Key));
}

const ItemData* ItemTable::GetData(const FName& StringKey)
{
	return static_cast<const ItemData*>(DataTable::GetData(StringKey));
}