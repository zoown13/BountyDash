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

	void CharScoreUp(unsigned int charScore);//플레이어의 점수를 받고 그 점수를 기반으로 게임값을 변경, 즉 더 많은 점수를 얻을수록 게임의 난이도를 상승

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
		int32 numCoinsForSpeedIncrease;//게임의 속도를 증가시키는데 코인이 얼마나 필요한지 결정

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float gameSpeedIncrease;//위의 변수값을 충족했을 때 오브젝트 속도가 얼마나 빨라질지 결정

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
