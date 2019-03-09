// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FieldObject.h"
#include "FieldItem.generated.h"

UCLASS(BlueprintType)
class SHOOTINGGAME_API AFieldItem : public AFieldObject
{
	GENERATED_BODY()	

public:
	EFieldObjectType GetType() const override { return EFieldObjectType::Item; }
};
