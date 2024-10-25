// Fill out your copyright notice in the Description page of Project Settings.


#include "ReturnPLayerTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AReturnPLayerTriggerBox::AReturnPLayerTriggerBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
}

// Called when the game starts or when spawned
void AReturnPLayerTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerStartPosition = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AReturnPLayerTriggerBox::MovePlayerBack);
}

// Called every frame
void AReturnPLayerTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReturnPLayerTriggerBox::MovePlayerBack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		OtherActor->SetActorLocation(PlayerStartPosition);
		UGameplayStatics::GetPlayerCharacter(this, 0)->GetCharacterMovement()->Velocity = FVector::ZeroVector;
		
	}
}