// Fill out your copyright notice in the Description page of Project Settings.

#include "Coin.h"
#include "Obstacle.h"
#include "BountyDashCharacter.h"
#include "Engine/World.h"
#include "BountyDashParticle.h"

#include "Components/StaticMeshComponent.h"


ACoin::ACoin() {
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(Mesh);
	Mesh->AttachTo(RootComponent);
	Mesh->SetCollisionProfileName("OverlapAllDynamic");
}

void ACoin::Tick(float DeltaTime){

Super::Tick(DeltaTime);
Mesh->AddLocalRotation(FRotator(5.0f, 0.0f, 0.0f));

}

void ACoin::MyOnActorOverlap(AActor* OverlappedActor, AActor* otherActor)
{
	if (otherActor->GetClass()->IsChildOf(AObstacle::StaticClass()) && !BeingPulled) {
		USphereComponent* thisSphere = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));

		USphereComponent* otherSphere = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));

		if (otherSphere) {
			AddActorLocalOffset(FVector(0.0f, 0.0f, (otherSphere->GetUnscaledSphereRadius()*2.0f) + Collider->GetUnscaledSphereRadius()));
		}
	}

	if (otherActor->GetClass()->IsChildOf(ABountyDashCharacter::StaticClass())) {

		ABountyDashParticle* particleSys = GetWorld()->SpawnActor<ABountyDashParticle>(ABountyDashParticle::StaticClass(), GetTransform());
		particleSys->SetKillPoint(GetKillPoint());


		ABountyDashCharacter* myChar = Cast<ABountyDashCharacter>(otherActor);
		myChar->ScoreUp();
		GetWorld()->DestroyActor(this);
	}
}



