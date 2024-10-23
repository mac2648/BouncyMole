// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Character2D.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;
class UFlipBookList;

UCLASS()
class MODULE2D_API ACharacter2D : public APaperCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputMappingContext* DefaultMovementMappingContext;

	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, category = "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, category = "Sprites")
	TSubclassOf<UFlipBookList> BookListClass;

protected:
	//holds the full list of sprites may require casting
	UPROPERTY()
	UFlipBookList* BookList;

	UPROPERTY(EditDefaultsOnly, category = "Movement")
	bool IsSideMovementOnly = true;

public:
	// Sets default values for this pawn's properties
	ACharacter2D();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//function can be overriten in case of different 2d movement
	virtual void Move(const FInputActionValue& Value);

	virtual void UpdateAnimation(const FVector& CharVelocity);
	virtual void UpdateRotation(const FVector& CharVelocity);

	inline UCameraComponent* GetCameraComp() const { return Camera; }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
