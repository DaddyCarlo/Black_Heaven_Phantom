// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animations/PlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if (APawn* PlayerPawn = TryGetPawnOwner())
	{
		PlayerCharacter = Cast<APlayerCharacter>(PlayerPawn);
		MovementComp = PlayerCharacter ? PlayerCharacter->GetCharacterMovement() : nullptr;
		
	}
}

void UPlayerAnimInstance::UpdateAnimProperties(float DeltaTime)
{
	APawn* Owner = TryGetPawnOwner();
	if (Owner != PlayerCharacter || IsValid (MovementComp))
	{
		PlayerCharacter = Cast<APlayerCharacter>(Owner);
		MovementComp = PlayerCharacter ? PlayerCharacter->GetCharacterMovement() : nullptr;
	}
		
	if (!PlayerCharacter || !MovementComp) return;
	
	const FVector Velocity = PlayerCharacter->GetVelocity();
	MovementSpeed = Velocity.Size2D(); // Ось Z не используется для скорости на земле
	
	// Проверка: В воздухе ли персонаж? (Is in Air?)
	bIsInAir = MovementComp->IsFalling();
	
	
	// Проверка: Есть ли на текущий момент активный ввод из устройства игрока для движения персонажа?
	bIsAccelerating = MovementComp->GetCurrentAcceleration().SizeSquared() > KINDA_SMALL_NUMBER;
}
