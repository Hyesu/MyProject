// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemData.h"
#include "DataTable/ItemTable.h"

FString UItemData::GetName(const FString& stringKey) const
{
	const ItemData* item{ GetItemTable()->GetData(*stringKey) };
	return item != nullptr ? item->name : "NoneName";
}

FString UItemData::GetType(const FString& stringKey) const
{
	const ItemData* item{ GetItemTable()->GetData(*stringKey) };
	return item != nullptr ? item->type.GetPlainNameString() : "None";
}

FString UItemData::GetSubType(const FString& stringKey) const
{
	const ItemData* item{ GetItemTable()->GetData(*stringKey) };
	return item != nullptr ? item->subType.GetPlainNameString() : "None";
}