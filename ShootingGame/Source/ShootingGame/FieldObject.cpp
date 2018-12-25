// Fill out your copyright notice in the Description page of Project Settings.

#include "FieldObject.h"

// Sets default values
AFieldObject::AFieldObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("COLLISION"));
	ModelComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MODEL"));

	RootComponent = CollisionComponent;
	ModelComponent->SetupAttachment(RootComponent);
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
	CollisionComponent->SetBoxExtent(FVector(40.f, 42.f, 30.f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MODEL_MESH(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1_C"));
	if (MODEL_MESH.Succeeded())
	{
		ModelComponent->SetStaticMesh(MODEL_MESH.Object);
	}
	ModelComponent->SetRelativeLocation(FVector(0.f, -3.5f, 7120.f));
}