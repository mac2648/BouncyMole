// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NextLevelTrigger.generated.h"

class UBoxComponent;
class ACharacter;
class UNextLevel;

UCLASS()
class BOUNCYMOLE_API ANextLevelTrigger : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	UWorld* Level;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UNextLevel> WidgetClass;
	
public:	
	// Sets default values for this actor's properties
	ANextLevelTrigger();

	UFUNCTION()
	void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
