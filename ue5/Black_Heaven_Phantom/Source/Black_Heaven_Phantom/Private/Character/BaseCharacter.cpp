// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/RotationMatrix.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->GetNavAgentPropertiesRef().bCanCrouch = true;
	}
	
}


