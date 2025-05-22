// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"



// Acts like begin play to create refrence to character
void UMyAnimInstance::NativeInitializeAnimation()
{
	MyCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	
}


// Acts like tick for animation and get speed
void UMyAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (MyCharacter == nullptr)
	{
		MyCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	}

	if (MyCharacter)
	{
		FVector Velocity = MyCharacter->GetVelocity();
		Velocity.Z = 0;
		Speed = Velocity.Size();

		bIsInAir = MyCharacter->GetCharacterMovement()->IsFalling();

		// Get Offset yaw for player in belnd spaces
		FRotator const AimRotation = MyCharacter->GetBaseAimRotation();
		FRotator const MovementRotation = UKismetMathLibrary::MakeRotFromX(MyCharacter->GetVelocity());

		Direction = UKismetMathLibrary::NormalizedDeltaRotator(AimRotation, MovementRotation).Yaw;
		
	}
}