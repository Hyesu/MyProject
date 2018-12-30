// Fill out your copyright notice in the Description page of Project Settings.

#include "JsonUtil.h"
#include "FileHelper.h"

JsonUtil::JsonUtil()
{
}

JsonUtil::~JsonUtil()
{
}


JsonUtil::Result JsonUtil::Init(const FString& FilePath)
{
	FString ResultString;
	if (FFileHelper::LoadFileToString(ResultString, *FilePath) == false)
	{
		return Result::Fail_NotExistFile;
	}

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResultString);
	if (FJsonSerializer::Deserialize(Reader, RootObject) == false)
	{		
		return Result::Fail_NotJsonFormat;
	}

	DataPath = FilePath;
	return Result::Succes;
}

JsonUtil::Result JsonUtil::ForEachArray(const JsonObjectPtr& ParentObject, const FString& ArrayFieldName, ForEachArrayFunc&& ForEachFunc)
{
	const TArray<JsonValuePtr>* OutArray;
	if (ParentObject->TryGetArrayField(ArrayFieldName, OutArray) == false)
	{
		return Result::Fail_NotExistField;
	}

	for (const JsonValuePtr& Value : *OutArray)
	{
		const JsonObjectPtr& Object{ Value->AsObject() };
		if (ForEachFunc(Object) == false)
		{
			return Result::Fail;
		}
	}

	return Result::Succes;
}

JsonUtil::Result JsonUtil::GetNameField(const JsonObjectPtr& JsonObject, const FString& FieldName, FName& outName)
{
	FString StringValue{ "None" }; // default Name value
	if (JsonObject->TryGetStringField(FieldName, StringValue) == false)
	{
		return Result::Fail_NotExistField;
	}

	outName = *StringValue;
	return Result::Succes;
}

JsonUtil::Result JsonUtil::GetVectorField(const JsonObjectPtr& JsonObject, const FString& FieldName, FVector& OutVector)
{
	const TArray<JsonValuePtr>* OutArrayPtr;
	if (JsonObject->TryGetArrayField(FieldName, OutArrayPtr) == false)
	{
		return Result::Fail_NotExistField;
	}

	constexpr int NUM_VECTOR_ELEMENT{ 3 }; // x, y, z
	if (OutArrayPtr->Num() != NUM_VECTOR_ELEMENT)
	{
		return Result::Fail_InvalidFormat;
	}

	const TArray<JsonValuePtr>& OutArray{ *OutArrayPtr };
	OutVector.X = OutArray[0]->AsNumber();
	OutVector.X = OutArray[1]->AsNumber();
	OutVector.X = OutArray[2]->AsNumber();

	return Result::Succes;
}