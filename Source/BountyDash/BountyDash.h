// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

template<typename T>
T* GetCustomGameMode(UWorld* worldContext) {
	return Cast<T>(worldContext->GetAuthGameMode());
}