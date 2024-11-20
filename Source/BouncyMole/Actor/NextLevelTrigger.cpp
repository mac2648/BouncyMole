// Fill out your copyright notice in the Description page of Project Settings.


#include "NextLevelTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BouncyMole/Widget/NextLevel.h"

// Sets default values
ANextLevelTrigger::ANextLevelTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
}

// Called when the game starts or when spawned
void ANextLevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ANextLevelTrigger::Trigger);
}

void ANextLevelTrigger::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		UGameplayStatics::GetPlayerCharacter(this, 0)->GetCharacterMovement()->Velocity = FVector::ZeroVector;

		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		Widget->AddToViewport();
		Widget->OnNativeDestruct.AddUObject(this, &ANextLevelTrigger::StartNextLevel);
	}
}

void ANextLevelTrigger::StartNextLevel(UUserWidget* Widget)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Level);
}