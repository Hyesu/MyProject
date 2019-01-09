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
};