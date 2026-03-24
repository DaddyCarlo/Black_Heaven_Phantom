// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "BaseCharacter.generated.h"

UCLASS(Abstract, NotBlueprintable)
class BLACK_HEAVEN_PHANTOM_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual void BeginPlay() override;
	
	virtual void Move(float Right, float Forward) {};
	virtual void LookUp(float Yaw, float Pitch) {};

	virtual void Mantle(){};
	
	// Aiming

	
	// Shooting

protected:


private:

	
	
};
