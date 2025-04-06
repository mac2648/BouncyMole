// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NextLevelTrigger.generated.h"

class UBoxComponent;
class ACharacter;
class UUserWidget;
class UNextLevel;
class UScoreScreen;

UCLASS()
class BOUNCYMOLE_API ANextLevelTrigger : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> Level;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UNextLevel> WidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UScoreScreen> ScoreWidgetClass;

	UScoreScreen* ScoreScreen = nullptr;
	
public:	
	// Sets default values for this actor's properties
	ANextLevelTrigger();

	UFUNCTION()
	void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void StartNextLevel(UUserWidget* Widget);

	UFUNCTION()
	void CloseScoreScreen();


};
