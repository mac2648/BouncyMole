#include "CameraFacingActor.h"
#include "BouncyMole/Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ACameraFacingActor::ACameraFacingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	SetRootComponent(Sprite);
}

// Called when the game starts or when spawned
void ACameraFacingActor::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		MasterCamera = Player->GetCameraComp();
	}
	else
	{
		throw "expected APlayerCharacter as the player class";
	}
}

// Called every frame
void ACameraFacingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateToCamera();
}

