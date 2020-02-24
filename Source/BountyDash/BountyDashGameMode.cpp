// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDashGameMode.h"
#include "BountyDashHUD.h"
#include "BountyDashCharacter.h"
#include "Engine/World.h"

ABountyDashGameMode::ABountyDashGameMode()
{
	//ABountyDashCharacter�� ���� �⺻ �� Ŭ���� ����
	DefaultPawnClass = ABountyDashCharacter::StaticClass();

	//BountyDashHUD�� �� ���� ����� �⺻ HUD Ŭ������ ����
	HUDClass = ABountyDashHUD::StaticClass();

	numCoinsForSpeedIncrease = 5;
	gameSpeed =10.0f;
	gameSpeedIncrease = 5.0f;
	gameLevel = 1;

	RunTime = 0.0f;
	bGameOver = false;
	startGameOverCount = false;
	timeTillGameOver = 2.0f;
	gameOverTimer = 0.0f;

}

void ABountyDashGameMode::CharScoreUp(unsigned int charScore)
{
	if (charScore != 0 && charScore%numCoinsForSpeedIncrease == 0) {
		gameSpeed += gameSpeedIncrease;
		gameLevel++;

	}
}

float ABountyDashGameMode::GetInvGameSpeed()
{
	return -gameSpeed;
}

float ABountyDashGameMode::GetGameSpeed()
{
	return gameSpeed;
}

int32 ABountyDashGameMode::GetGameLevel()
{
	return gameLevel;
}

void ABountyDashGameMode::ReduceGameSpeed()
{

	if (gameSpeed > 10.0f) {
		gameSpeed -= gameSpeedIncrease;
		gameLevel--;
	}
}

float ABountyDashGameMode::GetRunTime()
{
	return RunTime;
}

void ABountyDashGameMode::Tick(float DeltaSeconds)
{
	if(!startGameOverCount)
	{
		RunTime += DeltaSeconds;
	}
	else {

		gameOverTimer += DeltaSeconds;
		if (gameOverTimer >= timeTillGameOver) {
			bGameOver = true;
		}
	}

}

bool ABountyDashGameMode::GetGameOver()
{
	return bGameOver;
}

void ABountyDashGameMode::GameOver()
{
	startGameOverCount = true;
}

void ABountyDashGameMode::SetGamePaused(bool gamePaused)
{

	APlayerController* myPlayer = GetWorld()->GetFirstPlayerController();
	if (myPlayer != nullptr) {
		myPlayer->SetPause(gamePaused);
	}

}
