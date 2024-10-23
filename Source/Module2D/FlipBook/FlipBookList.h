// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FlipBookList.generated.h"

class UPaperFlipbook;
/*
 class that constains all the animations that will be used by a character2D, can be extended by inheritance
 */
UCLASS(config = Game, BlueprintType, Blueprintable)
class MODULE2D_API UFlipBookList : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Idle;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Moving;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Falling;
	
	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Jumping;
};