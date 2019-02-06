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
	UFUNCTION(BlueprintCallable)
	FString GetName(const FString& stringKey) const;

	UFUNCTION(BlueprintCallable)
	FString GetType(const FString& stringKey) const;

	UFUNCTION(BlueprintCallable)
	FString GetSubType(const FString& stringKey) const;

private:
};