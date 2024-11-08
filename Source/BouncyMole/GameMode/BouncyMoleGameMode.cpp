#include "BouncyMoleGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BouncyMole/Character/PlayerCharacter.h"
#include "BouncyMole/Pawn/BasicEnemy.h"


ABouncyMoleGameMode::ABouncyMoleGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	SoundComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio comp"));
}

void ABouncyMoleGameMode::GameOver()
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(this, ABasicEnemy::StaticClass(), Enemies);

	FTimerManager& TimeManager = GetWorld()->GetTimerManager();

	TimeManager.ClearAllTimersForObject(UGameplayStatics::GetPlayerPawn(this, 0));

	for (AActor* Enemy : Enemies)
	{
		TimeManager.ClearAllTimersForObject(Enemy);
	}

	if (GameOverWidgetClass)
	{
		UUserWidget* GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		GameOverWidget->AddToViewport();
	}

	SetActorTickEnabled(false);
}

void ABouncyMoleGameMode::BeginPlay()
{
	if (StartLevelWidget)
	{
		UUserWidget* GameStartWidget = CreateWidget<UUserWidget>(GetWorld(), StartLevelWidget);
		GameStartWidget->AddToViewport();
	}
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