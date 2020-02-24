// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BountyDashObject.h"
#include "Particles/ParticleSystemComponent.h"
#include "BountyDashParticle.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYDASH_API ABountyDashParticle : public ABountyDashObject
{
	GENERATED_BODY()
	
public:
	ABountyDashParticle();

	UPROPERTY()
		UParticleSystemComponent* particleSystem;
	
	
};
