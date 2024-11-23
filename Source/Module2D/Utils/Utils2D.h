#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PaperFlipbookComponent.h"
#include "Utils2D.generated.h"

class UPaperFlipbook;
class UPaperFlipbookComponent;

UCLASS()
class MODULE2D_API UUtils2D : public UObject
{
	GENERATED_BODY()

public:
	//plays the given animation once and adds a callback function to the end of the animation
	//used for playing animations and then going back to another state.
	template<class T, class Obj>
	static void PlayAnimationOnce(UPaperFlipbookComponent* Sprite, UPaperFlipbook* Animation, Obj* Object, void (T::*CallBackFunction)(), FName FuncName)
	{
		Sprite->SetFlipbook(Animation);
		Sprite->SetLooping(false);
		Sprite->Play();
		Sprite->OnFinishedPlaying.Clear();
		Sprite->OnFinishedPlaying.__Internal_AddDynamic(Object, CallBackFunction, FuncName);
	}

	UFUNCTION(BlueprintPure, Category = "Widget|Brush")
	static FSlateBrush MakeBrushFromSprite(UPaperSprite* Sprite, int32 Width, int32 Height);
};
