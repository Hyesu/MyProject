// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonReader.h"
#include "JsonSerializer.h"
#include <functional>
#include <vector>

/**
 * 
 */
using JsonObjectPtr = TSharedPtr<FJsonObject>;
using JsonValuePtr = TSharedPtr<FJsonValue>;
using ForEachArrayFunc = std::function<bool(const JsonObjectPtr& EachObject)>;

class SHOOTINGGAME_API JsonUtil
{
public:
	enum class Result
	{
		Success,
		Fail_NotExistFile,
		Fail_NotJsonFormat,
		Fail_NotExistField,
		Fail_InvalidFormat,
		Fail
	};

	JsonUtil();
	~JsonUtil();

	Result Init(const FString& FilePath);
	Result ForEachArray(const JsonObjectPtr& ParentObject, const FString& ArrayFieldName, ForEachArrayFunc&& ForEachFunc);
	Result GetNameField(const JsonObjectPtr& JsonObject, const FString& FieldName, FName& outName);
	Result GetVectorField(const JsonObjectPtr& JsonObject, const FString& FieldName, FVector& OutVector);
	Result GetStringListField(const JsonObjectPtr& JsonObject, const FString& FieldName, std::vector<FString>& OutVec);
	Result GetNameListField(const JsonObjectPtr& JsonObject, const FString& FieldName, std::vector<FName>& OutVec);

	const JsonObjectPtr& GetRootObject() const { return RootObject; }

private:
	FString DataPath;
	JsonObjectPtr RootObject;
};
