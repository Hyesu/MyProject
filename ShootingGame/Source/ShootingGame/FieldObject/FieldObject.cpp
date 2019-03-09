// Fill out your copyright notice in the Description page of Project Settings.

#include "FieldObject.h"
#include "ShootingGame.h"
#include "ShootingGameGameMode.h"
#include "Components/StaticMeshComponent.h"
#include "Manager/ResourceManager.h"

// Sets default values
AFieldObject::AFieldObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ModelComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MODEL"));
	RootComponent = ModelComponent;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MODEL_MESH(*DEFAULT_MODEL_PATH);
	if (MODEL_MESH.Succeeded())	{
		ModelComponent->SetStaticMesh(MODEL_MESH.Object);
	}
}

// Called when the game starts or when spawned
void AFieldObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFieldObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFieldObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AFieldObject::SetModelData(const FString& meshPath, const FVector& scale)
{
	UStaticMesh* mesh = RESOURCE_MGR->GetMesh(*meshPath);
	if (mesh != nullptr) {
		ModelComponent->SetStaticMesh(mesh);
	}
	ModelComponent->SetRelativeScale3D(scale);
}