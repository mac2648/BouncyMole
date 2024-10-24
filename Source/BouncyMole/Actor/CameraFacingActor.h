// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Module2D/Interface/RotateToCamera.h"
#include "CameraFacingActor.generated.h"

class UPaperFlipbookComponent;

UCLASS()
class BOUNCYMOLE_API ACameraFacingActor : public AActor, public IRotateToCamera
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* Sprite;
	
public:	
	// Sets default values for this actor's properties
	ACameraFacingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
