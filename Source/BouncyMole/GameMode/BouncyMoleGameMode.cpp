#include "BouncyMoleGameMode.h"
#include "Blueprint/UserWidget.h"

ABouncyMoleGameMode::ABouncyMoleGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABouncyMoleGameMode::GameOver()
{
	if (GameOverWidgetClass)
	{
		UUserWidget* GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		GameOverWidget->AddToViewport();
	}
}

void ABouncyMoleGameMode::Tick(float DeltaTime)
{
	if (TimeLeft >= 0)
	{
		TimeLeft -= DeltaTime;
	}
	

	if (TimeLeft <= 0)
	{
		GameOver();
	}
}