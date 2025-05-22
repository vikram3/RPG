// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"


//Declaration
/**
 * 
 */
UCLASS()
class RPG_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	// used in animation blueprints
	UFUNCTION(BlueprintCallable)
	void updateAnimationProperties(float DeltaTime);

	//We can initialize variables use them in blueprints
	virtual void NativeInitializeAnimation() override;

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	AMyCharacter* MyCharacter;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	bool bIsInAir;

	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	bool bIsBlocking;
	
};
