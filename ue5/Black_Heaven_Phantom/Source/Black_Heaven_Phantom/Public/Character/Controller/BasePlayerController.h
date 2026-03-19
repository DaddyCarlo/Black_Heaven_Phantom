// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BasePlayerController.generated.h"

class ABaseCharacter;
class UInputAction;
class UInputMappingContext;

UCLASS()
class BLACK_HEAVEN_PHANTOM_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetPawn(APawn* InPawn) override;
	virtual void BeginPlay() override;

protected:
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, Category="Enhanced Input")
	TObjectPtr<UInputMappingContext> PlayerMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Enhanced Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Enhanced Input")
	TObjectPtr<UInputAction> LookAction;

	//UPROPERTY(EditDefaultsOnly, Category="Enhanced Input")
	//TObjectPtr<UInputAction> MantleAction;

private:
	void EI_Move(const FInputActionValue& Value);
	void EI_Look(const FInputActionValue& Value);
	//void EI_Mantle();


	TWeakObjectPtr<ABaseCharacter> CachedBaseCharacter;
};
