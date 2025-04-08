// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReturnPLayerTriggerBox.generated.h"

class UBoxComponent;
class ACharacter;

UCLASS()
class BOUNCYMOLE_API AReturnPLayerTriggerBox : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UPROPERTY()
	UUserWidget* MessageWidget = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WidgetClass;

	FVector PlayerStartPosition;
	
public:	
	// Sets default values for this actor's properties
	AReturnPLayerTriggerBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void MovePlayerBack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HideWidget();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
