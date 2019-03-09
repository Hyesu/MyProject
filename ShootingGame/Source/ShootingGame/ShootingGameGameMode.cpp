// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShootingGameGameMode.h"
#include "ShootingGameCharacter.h"
#include "ShootingGame.h"
#include "UObject/ConstructorHelpers.h"
#include "DataTable/ItemTable.h"
#include "DataTable/SpawnTable.h"
#include "BlueprintCallable/ItemData.h"
#include "Manager/UIManager.h"
#include "Manager/ResourceManager.h"
#include "Manager/WorldManager.h"
#include "Kismet/GameplayStatics.h"

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
	GetDataManager()->Init();

	_uiManager = NewObject<UUIManager>(this);
	_uiManager->Init(GetWorld());

	_resourceManager = NewObject<UResourceManager>(this);
	_resourceManager->Init();

	_worldManager = NewObject<UWorldManager>(this);	
}

void AShootingGameGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	GetDataManager()->Finalize();
	GetDataManager()->DestroyInstance();
}

AShootingGameCharacter* AShootingGameGameMode::GetMyCharacter()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	return PC ? Cast<AShootingGameCharacter>(PC->GetPawn()) : nullptr;
}