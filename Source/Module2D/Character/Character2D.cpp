#include "Character2D.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Module2D/FlipBook/FlipBookList.h"

// Sets default values
ACharacter2D::ACharacter2D()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetSprite());
	SpringArm->SetWorldRotation(FRotator(0, 0, 90));
	SpringArm->TargetArmLength = 200;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ACharacter2D::BeginPlay()
{
	Super::BeginPlay();

	BookList = NewObject<UFlipBookList>(this, BookListClass);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMovementMappingContext, 0);
		}
	}
}

// Called every frame
void ACharacter2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Vel = GetCharacterMovement()->Velocity;

	UpdateAnimation(Vel);
	UpdateRotation(Vel);
}

// Called to bind functionality to input
void ACharacter2D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacter2D::Move);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}

void ACharacter2D::Move(const FInputActionValue& Value)
{
	FVector2D MoveVec = Value.Get<FVector2D>();

	FVector Dir;
	if (IsSideMovementOnly)
	{
		Dir = FVector(MoveVec.X, 0, 0);
	}
	else
	{
		Dir = FVector(MoveVec.X, MoveVec.Y, 0);
	}
	
	GetCharacterMovement()->AddInputVector(Dir);
}

void ACharacter2D::UpdateAnimation(const FVector& CharVelocity)
{
	if (CharVelocity.Z < 0)
	{
		GetSprite()->SetFlipbook(BookList->Falling);
	}
	else if (CharVelocity.Z > 0)
	{
		GetSprite()->SetFlipbook(BookList->Jumping);
	}
	else if (CharVelocity.Length() > 0)
	{
		GetSprite()->SetFlipbook(BookList->Moving);
	}
	else
	{
		GetSprite()->SetFlipbook(BookList->Idle);
	}
}

void ACharacter2D::UpdateRotation(const FVector& CharVelocity)
{
	if (CharVelocity.X > 0)
	{
		GetController()->SetControlRotation(FRotator(0, 0, 0));
	}
	else if (CharVelocity.X < 0)
	{
		GetController()->SetControlRotation(FRotator(0, 180, 0));
	}
}