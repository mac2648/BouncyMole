#include "BouncyMoleGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

ABouncyMoleGameMode::ABouncyMoleGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	SoundComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio comp"));
}

void ABouncyMoleGameMode::GameOver()
{
	if (GameOverWidgetClass)
	{
		UUserWidget* GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		GameOverWidget->AddToViewport();
	}

	SetActorTickEnabled(false);
}

void ABouncyMoleGameMode::Tick(float DeltaTime)
{
	if (TimeLeft >= 0)
	{
		TimeLeft -= DeltaTime;
	}

	if (TimeLeft <= 10 && !SoundComp->IsPlaying())
	{
		SoundComp->SetSound(Countdown);
		SoundComp->Play();
	}
	

	if (TimeLeft <= 0)
	{
		GameOver();
	}
}

void ABouncyMoleGameMode::AddTime()
{
	TimeLeft += 10.0f;

	if (SoundComp->IsPlaying())
	{
		SoundComp->Stop();
	}
}