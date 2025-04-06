// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncyMoleGameInstance.h"

void UBouncyMoleGameInstance::AddScore(int Value, ScoreType Type)
{
	PlayerScore += Value;
	ScoreChangeEvent.Broadcast(PlayerScore); 

	AmountOfEachScore[Type]++;
}

void UBouncyMoleGameInstance::MultiplyScore(float Value)
{ 
	PlayerScore *= Value;
	ScoreChangeEvent.Broadcast(PlayerScore); 

	AmountOfEachScore[ScoreType::TimeLeft] = Value;
}

void UBouncyMoleGameInstance::StartLevel()
{
	BeginOfLevelScore = PlayerScore;

	for (int Type = GreenSlimeGain; Type < NumScoreTypes; Type++)
	{
		AmountOfEachScore[Type] = 0;
	}
}

void UBouncyMoleGameInstance::ResetScore()
{
	PlayerScore = 0;
	BeginOfLevelScore = 0;
	ScoreChangeEvent.Broadcast(PlayerScore);

	for (int Type = GreenSlimeGain; Type < NumScoreTypes; Type++)
	{
		AmountOfEachScore[Type] = 0;
	}
}