// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/Player/PlayerCharacter.h"
#include "PlayerAnimInstance.generated.h"

class APlayerCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class BLACK_HEAVEN_PHANTOM_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateAnimProperties(float DeltaTime);

private:
	
	// Указатель на анимируемого персонажа 
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Characters", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APlayerCharacter> PlayerCharacter = nullptr;
	
	// Указатель на MovementComponent анимируемого персонажа
	UPROPERTY(Transient)
	TObjectPtr<UCharacterMovementComponent> MovementComp = nullptr;
	
	// Находится ли персонаж в воздухе (Например при прыжке или падении)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characters", meta = (AllowPrivateAccess = "true"))
	bool bIsInAir = false;
	
	// Переменная определяющая изменение скорости персонажа
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characters", meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating = false;
	
	// Переменная определяющая двигается ли сейчас персонаж
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characters", meta = (AllowPrivateAccess = "true"))
	bool bIsMoving = false;
	
	// Переменная определяющая скорость персонажа
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characters", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 0.0f;
};
