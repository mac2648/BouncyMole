// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Module2D/FlipBook/FlipBookList.h"
#include "PlayerBookList.generated.h"

/**
 * 
 */
UCLASS()
class BOUNCYMOLE_API UPlayerBookList : public UFlipBookList
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	UPaperFlipbook* BounceNormal;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Drill;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Death;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* HappyEnd;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Launch;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Rest;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* DrillLand;
};
