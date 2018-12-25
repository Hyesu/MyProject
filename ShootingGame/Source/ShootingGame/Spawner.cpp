// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "ShootingGame.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::Init()
{
	// todo: data driven

	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, FTimerDelegate::CreateLambda([this]() {
		SG_LOG("Spawn!");
	}), SpawnIntervalInSec, true);
}

void ASpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Init();
}