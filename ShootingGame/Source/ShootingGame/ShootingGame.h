// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(ShootingGame, Log, All);

#define SG_LOG(Format, ...) UE_LOG(ShootingGame, Warning, TEXT("%s - %d: %s"), *FString(__FUNCTION__), __LINE__, *FString::Printf(TEXT(Format), ##__VA_ARGS__))