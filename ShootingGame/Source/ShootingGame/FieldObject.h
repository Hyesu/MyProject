// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "FieldObject.generated.h"

UCLASS()
class SHOOTINGGAME_API AFieldObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitModel();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ModelComponent;
};
