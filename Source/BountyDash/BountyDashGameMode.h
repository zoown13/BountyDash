// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BountyDashGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYDASH_API ABountyDashGameMode : public AGameMode
{
	GENERATED_BODY()


	
public:
	ABountyDashGameMode();

	UPROPERTY()
		float gameSpeed;

	UPROPERTY(BlueprintReadWrite, Category = gameplay)
		int32 gameLevel;

	void CharScoreUp(unsigned int charScore);//�÷��̾��� ������ �ް� �� ������ ������� ���Ӱ��� ����, �� �� ���� ������ �������� ������ ���̵��� ���

	UFUNCTION()
		float GetInvGameSpeed();
	UFUNCTION()
		float GetGameSpeed();
	UFUNCTION()
		int32 GetGameLevel();

	void ReduceGameSpeed();

	float GetRunTime();
	
	UFUNCTION()
		virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
		bool GetGameOver();

	UFUNCTION()
		void GameOver();

	UFUNCTION()
		void SetGamePaused(bool gamePaused);


	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 numCoinsForSpeedIncrease;//������ �ӵ��� ������Ű�µ� ������ �󸶳� �ʿ����� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float gameSpeedIncrease;//���� �������� �������� �� ������Ʈ �ӵ��� �󸶳� �������� ����

	UPROPERTY()
		float RunTime;

	UPROPERTY()
		bool bGameOver;

	UPROPERTY()
		bool startGameOverCount;

	UPROPERTY()
		float timeTillGameOver;

	UPROPERTY()
		float gameOverTimer;
};
