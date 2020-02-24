// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.h" 
#include "ObstacleSpawner.generated.h"

UCLASS()
class BOUNTYDASH_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//��ֹ� �����Լ�
	void SpawnObstacle();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AObstacle>> ObstaclesToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class ATargetPoint*> SpawnTargets;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SpawnTimer;

	UPROPERTY()
		USceneComponent* Scene;

private:
	float KillPoint; //��ֹ� ���� ��ġ
	float SpawnPoint;//��ֹ� ���� ��ġ
	float timeSinceLastSpawn;//������ ��ֹ� �������� ���� �ð�
	
};
