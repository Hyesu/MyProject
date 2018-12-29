// Fill out your copyright notice in the Description page of Project Settings.

#include "FieldObject.h"
#include "ShootingGame.h"

// Sets default values
AFieldObject::AFieldObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ModelComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MODEL"));
	RootComponent = ModelComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MODEL_MESH(TEXT("/Game/Geometry/Meshes/1M_Cube"));
	if (MODEL_MESH.Succeeded())
	{
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

	InitModel();
}

void AFieldObject::InitModel()
{
	// todo: data driven	
}