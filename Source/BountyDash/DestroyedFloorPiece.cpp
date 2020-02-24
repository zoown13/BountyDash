// Fill out your copyright notice in the Description page of Project Settings.

#include "DestroyedFloorPiece.h"
#include "DestructibleMesh.h"

#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
ADestroyedFloorPiece::ADestroyedFloorPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	check(RootComponent);

	Destructible = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible"));
	check(Destructible);

	Destructible->AttachTo(RootComponent);
	Destructible->SetCollisionProfileName("OverlapAllDynamic");

	ConstructorHelpers::FObjectFinder<UDestructibleMesh>myDestMesh(TEXT("/Game/Geometry/Meshes/Destroyable_Mesh_DM.Destroyable_Mesh_DM"));
	if (myDestMesh.Succeeded()) {
		Destructible->SetDestructibleMesh(myDestMesh.Object);
	}

}

void ADestroyedFloorPiece::Death()
{
	GetWorld()->DestroyActor(this);
}

// Called when the game starts or when spawned
void ADestroyedFloorPiece::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle thisTimer;
	GetWorld()->GetTimerManager().SetTimer(thisTimer, this, &ADestroyedFloorPiece::Death, 4.0f, false);

}


