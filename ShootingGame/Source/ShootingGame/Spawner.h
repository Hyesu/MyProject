// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class SHOOTINGGAME_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	void PreSpawn();
	void Spawn();
	void PostSpawn();

	int32 GetMinCount() const { return _minCount; }
	int32 GetMaxCount() const { return _maxCount; }

private:
	void Init();

	FTimerHandle _spawnTimerHandle = {};

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* _meshComponent;

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	FName _spawnDataKey;

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float _spawnIntervalInSec{ 1.f };

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float _spawnRange{ 50.f };

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	bool _periodicSpawn{ false };

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	int32 _minCount{ 1 };

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	int32 _maxCount{ 1 };
};
