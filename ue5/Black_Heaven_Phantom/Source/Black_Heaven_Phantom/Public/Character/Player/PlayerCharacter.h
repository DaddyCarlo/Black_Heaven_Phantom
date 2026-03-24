// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class ABaseWeapon;
class UCameraComponent;
class USpringArmComponent;
class USceneComponent;

UCLASS(Blueprintable)
class BLACK_HEAVEN_PHANTOM_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	
	// Movement (Управление персонажа)
	virtual void Move(float Right, float Forward) override;
	virtual void LookUp(float Yaw, float Pitch) override;
	virtual	void Mantle() override;
	
	virtual void StartAiming() override;
	virtual void StopAiming() override;
	virtual bool IsAiming() const override;
	
	// Spawn weapon in character (Спавн оружия у персонажа)
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	ABaseWeapon* EquipWeapon(TSubclassOf<ABaseWeapon> Weapon);
	
protected:
	// Camera (Камера)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chracters| Camera")
	TObjectPtr<UCameraComponent> CameraComponent;
	// SpringArm (Штатив)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chracters| Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	// SceneComp (Компонент использующийся как оффсет для оружия)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chracters| Camera")
	TObjectPtr<USceneComponent> WeaponSocketHandR;

#pragma region SpawnWeaponSys
	
	// A Class selected in editor (Класс выбираемый в редакторе)
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	// TSubclassOf<ABaseWeapon> DefaultWeaponClass;
	
	// Selected weapon (Выбранное оружие)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<ABaseWeapon> CurrentWeapon;
	
	// Name Socket, the place where attached weapon (Имя сокета, место куда будет прикреплено оружие) 
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocketName = TEXT("WeaponSocket");
#pragma endregion
};
