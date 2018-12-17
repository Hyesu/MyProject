// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InvenWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API UInvenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindData(class UInventoryComponent* NewDataComponent);
	
private:
	TWeakObjectPtr<class UInventoryComponent> Data;
};
