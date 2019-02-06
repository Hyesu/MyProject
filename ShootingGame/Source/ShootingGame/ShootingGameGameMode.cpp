// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShootingGameGameMode.h"
#include "ShootingGameCharacter.h"
#include "ShootingGame.h"
#include "UObject/ConstructorHelpers.h"
#include "DataTable/ItemTable.h"
#include "DataTable/SpawnTable.h"
#include "BlueprintCallable/ItemData.h"

AShootingGameGameMode::AShootingGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AShootingGameGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	GetItemTable()->Init();
	_itemData = NewObject<UItemData>(this);

	GetSpawnTable()->Init();
}

void AShootingGameGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	GetItemTable()->DestroyInstance();
	GetSpawnTable()->DestroyInstance();
}