// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreScreen.h"
#include "BouncyMole/BouncyMoleGameInstance.h"
#include "Components/TextBlock.h"

void UScoreScreen::NativeConstruct()
{
	Super::NativeConstruct();

	UBouncyMoleGameInstance* GameInstance = GetGameInstance<UBouncyMoleGameInstance>();

	const short* Scores = GameInstance->GetAmountOfEachScore();

	for (int Type = GreenSlimeGain; Type < NumScoreTypes; Type++)
	{
		FString ScoreString;
		switch(Type)
		{
		case GreenSlimeGain:
			ScoreString.Append("+5 x ");
			ScoreString.AppendInt(Scores[GreenSlimeGain]);
			GreenSlimeScoreGain->SetText(FText::FromString(ScoreString));
			break;

		case GreenSlimeLost:
			ScoreString.Append("-5 x ");
			ScoreString.AppendInt(Scores[GreenSlimeLost]);
			GreenSlimeScoreLost->SetText(FText::FromString(ScoreString));
			break;

		case BlueSlimeGain:
			ScoreString.Append("+10 x ");
			ScoreString.AppendInt(Scores[BlueSlimeGain]);
			BlueSlimeScoreGain->SetText(FText::FromString(ScoreString));
			break;

		case BlueSlimeLost:
			ScoreString.Append("-10 x ");
			ScoreString.AppendInt(Scores[BlueSlimeLost]);
			BlueSlimeScoreLost->SetText(FText::FromString(ScoreString));
			break;

		case QueenSlimeGain:
			ScoreString.Append("+20 x ");
			ScoreString.AppendInt(Scores[QueenSlimeGain]);
			QueenSlimeScoreGain->SetText(FText::FromString(ScoreString));
			break;

		case QueenSlimeLost:
			ScoreString.Append("-20 x ");
			ScoreString.AppendInt(Scores[QueenSlimeLost]);
			QueenSlimeScoreLost->SetText(FText::FromString(ScoreString));
			break;

		case ExtraLifes:
			ScoreString.Append("10 x ");
			ScoreString.AppendInt(Scores[ExtraLifes]);
			ExtraLivesScore->SetText(FText::FromString(ScoreString));
			break;

		case TimeLeft:
			ScoreString.Append("x");
			ScoreString.AppendInt(Scores[TimeLeft]);
			TimeExtraScore->SetText(FText::FromString(ScoreString));
			break;
		}
	}

	FString BeginLevelScoreString("Starting Score: ");
	BeginLevelScoreString.AppendInt(GameInstance->GetBeginOfLevelScore());
	BeginLevelScore->SetText(FText::FromString(BeginLevelScoreString));

	FString CurrentScoreString("Total Score: ");
	CurrentScoreString.AppendInt(GameInstance->GetPlayerScore());
	CurrentScore->SetText(FText::FromString(CurrentScoreString));
}