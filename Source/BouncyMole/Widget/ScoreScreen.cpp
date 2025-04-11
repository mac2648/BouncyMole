// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreScreen.h"
#include "BouncyMole/BouncyMoleGameInstance.h"
#include "Components/TextBlock.h"

void UScoreScreen::NativeConstruct()
{
	Super::NativeConstruct();

	UBouncyMoleGameInstance* GameInstance = GetGameInstance<UBouncyMoleGameInstance>();

	const short* Scores = GameInstance->GetAmountOfEachScore();

	FString Score = "";
	Score.AppendInt(Scores[DamageTaken]);
	EnemyScoreLost->SetText(FText::FromString(Score));
	Score.Empty();

	Score.AppendInt(Scores[EnemiesKilled]);
	EnemyScoreGain->SetText(FText::FromString(Score));
	Score.Empty();

	Score.AppendInt(Scores[TimeLeft]);
	TimeExtraScore->SetText(FText::FromString(Score));
	Score.Empty();

	Score.AppendInt(Scores[ExtraLifes]);
	ExtraLivesScore->SetText(FText::FromString(Score));

	FString BeginLevelScoreString("Starting Score: ");
	BeginLevelScoreString.AppendInt(GameInstance->GetBeginOfLevelScore());
	BeginLevelScore->SetText(FText::FromString(BeginLevelScoreString));

	FString CurrentScoreString("Total Score: ");
	CurrentScoreString.AppendInt(GameInstance->GetPlayerScore());
	CurrentScore->SetText(FText::FromString(CurrentScoreString));
}