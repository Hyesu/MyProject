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

	class UUIManager* GetUIManager() const { return _uiManager; }
	class UResourceManager* GetResourceManager() const { return _resourceManager; }
	class UWorldManager* GetWorldManager() const { return _worldManager; }
	class AShootingGameCharacter* GetMyCharacter();

private:
	UPROPERTY()
	UUIManager* _uiManager;

	UPROPERTY()
	UResourceManager* _resourceManager;

	UPROPERTY()
	UWorldManager* _worldManager;
};

#define UI_MGR			((AShootingGameGameMode*)GetWorld()->GetAuthGameMode())->GetUIManager()
#define RESOURCE_MGR	((AShootingGameGameMode*)GetWorld()->GetAuthGameMode())->GetResourceManager()
#define WORLD_MGR		((AShootingGameGameMode*)GetWorld()->GetAuthGameMode())->GetWorldManager()
#define MY_CHARACTER	((AShootingGameGameMode*)GetWorld()->GetAuthGameMode())->GetMyCharacter()