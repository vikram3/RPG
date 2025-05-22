// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Camera Boom
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComponent ->SetupAttachment(RootComponent);
	SpringArmComponent-> TargetArmLength = 400.f;
	SpringArmComponent-> bUsePawnControlRotation = true;

	// Follow Camera
	FollowCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	FollowCameraComponent-> bUsePawnControlRotation = false;

	// Jump Settings
	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add input mapping content
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		//Get Local player subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Add Input Context
			Subsystem->AddMappingContext(InputMapping,0);
		}
	}
	
}

void AMyCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();
	if (IsValid(Controller))
	{
		// Get Forward direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw , 0);

		// Rotation Matric
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		// Add movement input
		AddMovementInput(ForwardDirection,InputVector.Y);
		AddMovementInput(RightDirection,InputVector.X);
	}
}

void AMyCharacter::Look(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y); 
	}
}

void AMyCharacter::Jump()
{
	// call parent class jump function
	Super::Jump();

	if (GetCharacterMovement()->IsMovingOnGround())
	{
		// Get Current forward velocity
		FVector ForwardVelocity = GetVelocity();
		ForwardVelocity.Z = 0;

		// Define jump vertical velocity
		float JumpVerticalVelocity = GetCharacterMovement()-> JumpZVelocity;

		// Combine Current Forward velocity with jump vertical velocity
		FVector JumpVelocity = ForwardVelocity + FVector(0,0 , JumpVerticalVelocity);

		// Launch Charactr with the combined velocity
		LaunchCharacter(JumpVelocity, true, true);
		
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement actions
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Movement actions
		Input-> BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		Input-> BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		Input-> BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);
		
	}

}

