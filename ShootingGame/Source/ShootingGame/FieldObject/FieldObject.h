// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "FieldObject.generated.h"

UENUM()
enum class EFieldObjectType : uint8
{
	Invalid,
	Item
};

UCLASS(BlueprintType)
class SHOOTINGGAME_API AFieldObject : public AActor
{
	GENERATED_BODY()
	
public:
	AFieldObject();
	virtual ~AFieldObject() {}

protected:
	virtual void BeginPlay() override;

public:	
	virtual EFieldObjectType GetType() const { return EFieldObjectType::Invalid; }

	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	void SetModelData(const FString& meshPath, const FVector& scale);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ModelComponent;

	UPROPERTY(BlueprintReadOnly)
	FName DataStringKey;
};
