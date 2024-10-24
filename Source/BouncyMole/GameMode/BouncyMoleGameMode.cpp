#include "BouncyMoleGameMode.h"
#include "Blueprint/UserWidget.h"

void ABouncyMoleGameMode::GameOver()
{
	if (GameOverWidgetClass)
	{
		UUserWidget* GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		GameOverWidget->AddToViewport();
	}
}