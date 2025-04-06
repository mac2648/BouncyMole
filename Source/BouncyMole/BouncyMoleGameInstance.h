// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BouncyMoleGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreChangeEvent, int, NewScore);
/**
 * 
 */
UCLASS()
class BOUNCYMOLE_API UBouncyMoleGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FScoreChangeEvent ScoreChangeEvent;
	
private:
	int PlayerScore = 0;

public:
	void AddScore(int Value) { PlayerScore += Value; ScoreChangeEvent.Broadcast(PlayerScore); }
	void MultiplyScore(float Value) { PlayerScore *= Value; ScoreChangeEvent.Broadcast(PlayerScore); }

	UFUNCTION(BlueprintCallable)
	int GetPlayerScore() const { return PlayerScore; }

	UFUNCTION(BlueprintCallable)
	void ResetScore() { PlayerScore = 0; ScoreChangeEvent.Broadcast(PlayerScore); }

};
