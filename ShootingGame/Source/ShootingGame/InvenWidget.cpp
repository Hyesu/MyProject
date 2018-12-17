// Fill out your copyright notice in the Description page of Project Settings.

#include "InvenWidget.h"
#include "InventoryComponent.h"

void UInvenWidget::BindData(UInventoryComponent* NewDataComponent)
{
	if (NewDataComponent == nullptr)
		return;

	Data = NewDataComponent;
	NewDataComponent->OnInvenChanged.AddLambda([]() {
		// todo: ui change apply
	});
}