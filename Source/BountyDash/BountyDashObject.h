// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "BountyDashObject.generated.h"

UCLASS()
class BOUNTYDASH_API ABountyDashObject : public AActor
{
	GENERATED_BODY()

	float KillPoint;//�ڽ��� �������� ���� �����ϴ� ��ġ
	
public:
	// �� ������ �Ӽ� �⺻���� ������
	ABountyDashObject();

	// ������ ���۵ǰų� �����Ǿ��� �� ȣ��� 
	virtual void BeginPlay() override;

	// �� ������ ȣ���
	virtual void Tick(float DeltaSeconds) override;

	void SetKillPoint(float point);
	float GetKillPoint();

protected:
	UFUNCTION()
		virtual void MyOnActorOverlap(AActor* OverlappedActor, AActor* otherActor);

	UFUNCTION()
		virtual void MyOnActorEndOverlap(AActor* OverlappedActor, AActor* otherActor);

	UPROPERTY(EditAnywhere)
		USphereComponent* Collider;
	
};
