// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "FlipBookImage.generated.h"

class UPaperFlipbook;
class UPaperSprite;
class UTextureRenderTarget2D;
/**
 * 
 */
UCLASS()
class MODULE2D_API UFlipBookImage : public UImage
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Sprite;

	UPROPERTY(EditAnywhere)
	FVector2D Size;

	UPROPERTY(EditAnywhere)
	bool IsLooping = false;

	float Timer = 0.0;

	class FTSTicker::FDelegateHandle TickHandle;

public:
	UFlipBookImage();
	virtual ~UFlipBookImage();

	UFUNCTION(BlueprintCallable)
	virtual bool SetImageByTime(float Time);

protected:

};