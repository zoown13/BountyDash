// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BountyDashObject.h"
#include "BountyDashPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYDASH_API ABountyDashPowerUp : public ABountyDashObject
{
	GENERATED_BODY()
	
public:
	// �� ������ �Ӽ� �⺻���� ������
	ABountyDashPowerUp();

	UFUNCTION()
		virtual void MyOnActorOverlap(AActor* OverlappedActor, AActor* otherActor) override;

protected:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

private:
	class UPowerUpObject* PowerUp;
	
	
};
