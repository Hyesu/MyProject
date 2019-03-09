// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SHOOTINGGAME_API UItemData : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category="Data|Item")
	static FString GetItem_Name(const FName& stringKey);

	UFUNCTION(BlueprintPure, Category = "Data|Item")
	static FString GetItem_Type(const FName& stringKey);

	UFUNCTION(BlueprintPure, Category = "Data|Item")
	static FString GetItem_SubType(const FName& stringKey);
};