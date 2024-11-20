// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BouncyMoleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BOUNCYMOLE_API ABouncyMoleGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditDefaultsOnly, category = "UI")
	TSubclassOf<UUserWidget> StartLevelWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	float TimeLeft = 120.0f;

	UPROPERTY(EditdefaultsOnly, category = "Sound")
	class USoundCue* Countdown;

	UPROPERTY()
	class UAudioComponent* SoundComp;
	
public:
	ABouncyMoleGameMode();

	UFUNCTION(BlueprintCallable)
	float GetTimeLeft() const { return TimeLeft; }

	void GameOver();
	void AddTime();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
