// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class BLACK_HEAVEN_PHANTOM_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	
	// Movement
	virtual void Move(float Right, float Forward) override;
	virtual void LookUp(float Yaw, float Pitch) override;
	virtual	void Mantle() override;
	
	virtual void StartAiming() override;
	virtual void StopAiming() override;
	virtual bool IsAiming() const override;
protected:
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chracters| Camera")
	TObjectPtr<UCameraComponent> CameraComponent;
	// SpringArm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chracters| Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	
};
