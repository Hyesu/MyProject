// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameGameMode.generated.h"

UCLASS(minimalapi)
class AShootingGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootingGameGameMode();

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	void Logout(AController* Exiting) override;

	UFUNCTION(BlueprintCallable)
	class UItemData* GetItemData() const { return _itemData; }

	class UUIManager* GetUIManager() const { return _uiManager; }
	class UResourceManager* GetResourceManager() const { return _resourceManager; }

private:
	UPROPERTY()
	UItemData* _itemData;

	UPROPERTY()
	UUIManager* _uiManager;

	UPROPERTY()
	UResourceManager* _resourceManager;
};

#define UI_MGR			((AShootingGameGameMode*)GetWorld()->GetAuthGameMode())->GetUIManager()
#define RESOURCE_MGR	((AShootingGameGameMode*)GetWorld()->GetAuthGameMode())->GetResourceManager()