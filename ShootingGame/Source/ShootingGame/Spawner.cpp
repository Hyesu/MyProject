// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "ShootingGame.h"
#include "FieldObject.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RANGE"));
	RootComponent = MeshComponent;
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

	FVector Location{ GetActorLocation() };
	float Range{ SpawnRange };
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, FTimerDelegate::CreateLambda([this, Location, Range]() {

		FVector TargetLocation{ Location };
		TargetLocation.X += FMath::RandRange(-Range, Range);
		TargetLocation.Y += FMath::RandRange(-Range, Range);
		TargetLocation.Z += FMath::RandRange(-Range, Range);

		auto NewFdObject = GetWorld()->SpawnActor<AFieldObject>(TargetLocation, FRotator::ZeroRotator);

	}), SpawnIntervalInSec, true);
}

void ASpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Init();
}