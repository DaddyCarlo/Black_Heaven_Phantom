// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerCharacter.h"
#include "Weapons/BaseWeapon.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
	WeaponSocketHandR = CreateDefaultSubobject<USceneComponent>("WeaponOffset");
	WeaponSocketHandR->SetupAttachment(GetMesh(), WeaponSocketName);
	
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 145.f;
	SpringArmComponent->ProbeSize = 20.f;
	SpringArmComponent->bDoCollisionTest = true;
	
	SpringArmComponent->SocketOffset = FVector(0, 35.f, 65.f);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
	
	CameraComponent->FieldOfView = 75.f;
	
	
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	
}

#pragma region Basic Movement
void APlayerCharacter::Move(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void APlayerCharacter::LookUp(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}
#pragma endregion
void APlayerCharacter::Mantle()
{
	// Placeholder: connect your mantle component/ability here.
}

void APlayerCharacter::StartAiming()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Aim"));

	bIsAiming = true;
	CameraComponent->SetFieldOfView(60.f);
	GetCharacterMovement()->MaxWalkSpeed = 225.f;
}

void APlayerCharacter::StopAiming()
{
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Aiming End"));

	bIsAiming = false;
	CameraComponent->SetFieldOfView(75.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void APlayerCharacter::StartShooting()
{
	bIsShooting = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Shooting"));
	UE_LOG(LogTemp, Warning, TEXT("Shooting"));
	
	// TO DO: Разобраться со стрельбой, изменить способ ввода
}

void APlayerCharacter::StopShooting()
{
	bIsShooting = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Stop Shooting"));
	UE_LOG(LogTemp, Warning, TEXT("Stop Shooting"));
	
	// TO DO: Разобраться со стрельбой, изменить способ ввода
}

ABaseWeapon* APlayerCharacter::EquipWeapon(TSubclassOf<ABaseWeapon> WeaponClass)
{
	// If Weapon class is not selected, exit the function (Если класс оружия не выбран, выходим из функции.)
	if (!WeaponClass)
	{
		return nullptr;
	}
	
	// If weapon is already selected, destroy him (Если оружие уже выбрано, уничтожаем его)
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}
	
	// Spawn Parameters (Настройка спавна)
	FActorSpawnParameters SpawnParams;
	
	SpawnParams.Owner = this; // Owner is Player (Владелец - игрок)
	SpawnParams.Instigator = GetInstigator(); // We determine: Who caused the action? (Определяем: Кто вызвал действие?)
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // Ignore Collision (Игнорируем коллизии)
	
	// Spawn Weapon (Спавн оружия)
	ABaseWeapon* NewWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass, FTransform::Identity, SpawnParams);
	
	// Check: If the weapon is not spawn, exit the function (Если оружие не создалось, выходим из функции)
	if (!NewWeapon)
	{
		return nullptr;
	}
	
	// Attached the weapon to Socket (Прикрепляем оружие к сокету)
	NewWeapon->AttachToComponent(WeaponSocketHandR, FAttachmentTransformRules::SnapToTargetNotIncludingScale); //, WeaponSocketName);
	
	// Set weapon owner (Устанавливаем владельца оружия)
	NewWeapon->SetOwner(this);
	
	// Saving the weapon as selected (Записываем оружие как выбранное)
	CurrentWeapon = NewWeapon;
	
	// Return weapon (Возвращаем оружие)
	return NewWeapon;
}
