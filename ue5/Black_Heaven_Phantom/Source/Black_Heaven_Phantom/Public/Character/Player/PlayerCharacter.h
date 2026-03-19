// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

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
	
protected:
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chracters| Camera")
	class UCameraComponent* CameraComponent;
	// SpringArm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chracters| Camera")
	class USpringArmComponent* SpringArmComponent;
};
