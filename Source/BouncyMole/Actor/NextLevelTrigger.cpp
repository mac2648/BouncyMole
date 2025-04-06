// Fill out your copyright notice in the Description page of Project Settings.


#include "NextLevelTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BouncyMole/Widget/NextLevel.h"
#include "BouncyMole/BouncyMoleGameInstance.h"
#include "BouncyMole/GameMode/BouncyMoleGameMode.h"
#include "BouncyMole/Character/PlayerCharacter.h"
#include "BouncyMole/Widget/ScoreScreen.h"

// Sets default values
ANextLevelTrigger::ANextLevelTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
}

// Called when the game starts or when spawned
void ANextLevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ANextLevelTrigger::Trigger);
}

void ANextLevelTrigger::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		UGameplayStatics::GetPlayerCharacter(this, 0)->GetCharacterMovement()->Velocity = FVector::ZeroVector;

		const int LifeBonusScore = 10;
		int PlayerHPScore = Cast<APlayerCharacter>(OtherActor)->GetCurrentHp();
		for (int i = 0; i < PlayerHPScore; i++)
		{
			GetGameInstance<UBouncyMoleGameInstance>()->AddScore(LifeBonusScore, ScoreType::ExtraLifes);
		}

		float Multiplier = 1;
		if (ABouncyMoleGameMode* GameMode = Cast<ABouncyMoleGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			float TimeTaken = GameMode->MaxTimeLeft - GameMode->GetTimeLeft();

			if (TimeTaken < 30.0f)
			{
				Multiplier = 3;
			}
			else if (TimeTaken < 60.f)
			{
				Multiplier = 2;
			}
			else if (TimeTaken < 90.0f)
			{
				Multiplier = 1.5;
			}
			else
			{
				Multiplier = 1;
			}
		}

		GetGameInstance<UBouncyMoleGameInstance>()->MultiplyScore(Multiplier);

		ScoreScreen = CreateWidget<UScoreScreen>(GetWorld(), ScoreWidgetClass);
		ScoreScreen->AddToViewport();

		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &ANextLevelTrigger::CloseScoreScreen, 3);
	}
}

void ANextLevelTrigger::StartNextLevel(UUserWidget* Widget)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Level);
}

void ANextLevelTrigger::CloseScoreScreen()
{
	ScoreScreen->RemoveFromParent();

	GetGameInstance<UBouncyMoleGameInstance>()->StartLevel();

	UNextLevel* Widget = CreateWidget<UNextLevel>(GetWorld(), WidgetClass);
	Widget->SetLevel(Level);
	Widget->AddToViewport();
	Widget->OnNativeDestruct.AddUObject(this, &ANextLevelTrigger::StartNextLevel);
}