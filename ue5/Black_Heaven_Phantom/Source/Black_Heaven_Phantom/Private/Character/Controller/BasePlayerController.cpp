// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Controller/BasePlayerController.h"
#include "Character/Player/PlayerCharacter.h"
#include "EnhancedInputComponent.h" 
#include "HeadMountedDisplayTypes.h"
#include "InputAction.h"

void ABasePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedBaseCharacter = Cast<APlayerCharacter>(InPawn);
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!PlayerMappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: PlayerMappingContext is not set."), *GetName());
		return;
	}

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInput)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: InputComponent is not EnhancedInputComponent."), *GetName());
		return;
	}

	if (MoveAction)
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABasePlayerController::EI_Move);
	}

	if (LookAction)
	{
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABasePlayerController::EI_Look);
	}
	if (AimingAction)
	{
		EnhancedInput->BindAction(AimingAction, ETriggerEvent::Triggered, this, &ABasePlayerController::EI_AimStart);
		EnhancedInput->BindAction(AimingAction, ETriggerEvent::Completed, this, &ABasePlayerController::EI_AimStop);
	}
	if (ShootingAction)
	{
		EnhancedInput->BindAction(ShootingAction, ETriggerEvent::Started, this, &ABasePlayerController::EI_ShootingStart);
		EnhancedInput->BindAction(ShootingAction, ETriggerEvent::Completed, this, &ABasePlayerController::EI_ShootingStop);
	}
	// if (MantleAction)
	// {
	// 	EnhancedInput->BindAction(MantleAction, ETriggerEvent::Started, this, &ABasePlayerController::EI_Mantle);
	// }

}

void ABasePlayerController::EI_Move(const FInputActionValue& Value)
{
	if (APlayerCharacter* ControlledBaseCharacter = CachedBaseCharacter.Get())
	{
		FVector2D MovementVector = Value.Get<FVector2D>();
		ControlledBaseCharacter->Move(MovementVector.X, MovementVector.Y);
	}
}

void ABasePlayerController::EI_Look(const FInputActionValue& Value)
{
	if (APlayerCharacter* ControlledBaseCharacter = CachedBaseCharacter.Get())
	{
		FVector2D LookAxisVector = Value.Get<FVector2D>();
		ControlledBaseCharacter->LookUp(LookAxisVector.X, LookAxisVector.Y);
	}
}

void ABasePlayerController::EI_AimStart()
{
	if (APlayerCharacter* ControlledBaseCharacter = CachedBaseCharacter.Get())
	{
		ControlledBaseCharacter->StartAiming();
	}
}

void ABasePlayerController::EI_AimStop()
{
	if(APlayerCharacter* ControlledBaseCharacter = CachedBaseCharacter.Get())
	{
		ControlledBaseCharacter->StopAiming();
	}
}

void ABasePlayerController::EI_ShootingStart()
{
	if (APlayerCharacter* ControlledBaseCharacter = CachedBaseCharacter.Get(); ControlledBaseCharacter && ControlledBaseCharacter->bIsAiming && !ControlledBaseCharacter->bIsShooting)
	{
		ControlledBaseCharacter->StartShooting();
	}
}

void ABasePlayerController::EI_ShootingStop()
{
	if (APlayerCharacter* ControlledBaseCharacter = CachedBaseCharacter.Get())
	{
		ControlledBaseCharacter->StopShooting();
	}
}


// void ABasePlayerController::EI_Mantle()
// {
// 	if (ABaseCharacter* ControlledBaseCharacter = CachedBaseCharacter.Get())
// 	{
// 		ControlledBaseCharacter->Mantle();
// 	}
// }

