// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemData.h"
#include "DataTable/ItemTable.h"

FString UItemData::GetItem_Name(const FString& stringKey)
{
	const ItemData* item{ GetItemTable()->GetData(*stringKey) };
	return item != nullptr ? item->name : "NoneName";
}

FString UItemData::GetItem_Type(const FString& stringKey)
{
	const ItemData* item{ GetItemTable()->GetData(*stringKey) };
	return item != nullptr ? item->type.GetPlainNameString() : "None";
}

FString UItemData::GetItem_SubType(const FString& stringKey)
{
	const ItemData* item{ GetItemTable()->GetData(*stringKey) };
	return item != nullptr ? item->subType.GetPlainNameString() : "None";
}