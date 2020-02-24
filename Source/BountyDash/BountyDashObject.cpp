// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDashObject.h"
#include "BountyDash.h"
#include "BountyDashGameMode.h"


// Sets default values
ABountyDashObject::ABountyDashObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Colllider"));
	check(Collider);

	RootComponent = Collider;
	Collider->SetCollisionProfileName("OverlapAllDynamic");

	OnActorBeginOverlap.AddDynamic(this, &ABountyDashObject::MyOnActorOverlap);
	OnActorBeginOverlap.AddDynamic(this, &ABountyDashObject::MyOnActorEndOverlap);
}

// Called when the game starts or when spawned
void ABountyDashObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABountyDashObject::MyOnActorOverlap(AActor* OverlappedActor, AActor* otherActor)
{
}

void ABountyDashObject::MyOnActorEndOverlap(AActor* OverlappedActor, AActor* otherActor)
{
}

// Called every frame
void ABountyDashObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float gameSpeed = GetCustomGameMode<ABountyDashGameMode>(GetWorld())->GetInvGameSpeed();

	AddActorWorldOffset(FVector(gameSpeed, 0.0f, 0.0f));

	if (GetActorLocation().X < KillPoint) {

		Destroy();

	}

}

void ABountyDashObject::SetKillPoint(float point)
{
	KillPoint = point;
}

float ABountyDashObject::GetKillPoint()
{
	return KillPoint;
}

