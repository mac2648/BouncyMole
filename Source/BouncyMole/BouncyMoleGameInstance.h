// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BouncyMoleGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreChangeEvent, int, NewScore);

enum ScoreType : int
{
	EnemiesKilled,
	DamageTaken,
	ExtraLifes,
	TimeLeft,

	NumScoreTypes
};

UCLASS()
class BOUNCYMOLE_API UBouncyMoleGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FScoreChangeEvent ScoreChangeEvent;
	
private:
	int PlayerScore = 0;
	int BeginOfLevelScore = 0;

	short AmountOfEachScore[ScoreType::NumScoreTypes] = {};

public:
	void AddScore(int Value, ScoreType Type);
	void MultiplyScore(float Value);
	void StartLevel();

	const short* GetAmountOfEachScore() const { return AmountOfEachScore; }
	inline int GetBeginOfLevelScore() const { return BeginOfLevelScore; }

	UFUNCTION(BlueprintCallable)
	int GetPlayerScore() const { return PlayerScore; }

	UFUNCTION(BlueprintCallable)
	void ResetScore();

};
