// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

const FName APlayerCharacter::LookNorthBinding("LookNorth");
const FName APlayerCharacter::LookEastBinding("LookEast");
const FName APlayerCharacter::MoveNorthBinding("MoveNorth");
const FName APlayerCharacter::MoveEastBinding("MoveEast");

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 95.0f);
	*/

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 10000.0f, 0.0f); // ...at this rotation rate
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Create look direction vector
	const float LookNorthValue = GetInputAxisValue(LookNorthBinding);
	const float LookEastValue = GetInputAxisValue(LookEastBinding);
	LookDirection = FVector(LookNorthValue, LookEastValue, 0.f);

	// If non-zero size, rotate this actor
	if (LookDirection.SizeSquared() > 0.0f)
	{
		const FRotator LookRotation = LookDirection.Rotation();

		RootComponent->SetWorldRotation(LookRotation);
	}

	// Create move direction vector
	const float MoveNorthValue = GetInputAxisValue(MoveNorthBinding);
	const float MoveEastValue = GetInputAxisValue(MoveEastBinding);
	MoveDirection = FVector(MoveNorthValue, MoveEastValue, 0.f);

	// If non-zero size, move this actor
	if (MoveDirection.SizeSquared() > 0.0f)
	{
		AddMovementInput(MoveDirection, 1.f);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	*/

	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis(MoveNorthBinding);
	PlayerInputComponent->BindAxis(MoveEastBinding);

	PlayerInputComponent->BindAxis(LookNorthBinding);
	PlayerInputComponent->BindAxis(LookEastBinding);

	//PlayerInputComponent->BindAction("MainFire", IE_Pressed, this, &CLASSNAME::MainFire);
}

void APlayerCharacter::DealDamage(float damage)
{
	m_currentHealth -= damage;

	if (m_currentHealth <= 0.f)
	{
		//	respawn logic or something
		Destroy();
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
/*
void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
*/
void APlayerCharacter::MainFire()
{
}

void APlayerCharacter::AltFire()
{
}

void APlayerCharacter::AimedAbility1()
{
}

void APlayerCharacter::AimedAbility2()
{
}
