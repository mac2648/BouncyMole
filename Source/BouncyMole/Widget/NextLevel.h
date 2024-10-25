// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NextLevel.generated.h"

/**
 * 
 */
UCLASS()
class BOUNCYMOLE_API UNextLevel : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	UWorld* Level;

public:
	void SetLevel(UWorld* NewLevel) { Level = NewLevel; }
};
