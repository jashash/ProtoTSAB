// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PROTOTSAB_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DealDamage(float damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MainFire();
	virtual void AltFire();
	virtual void AimedAbility1();
	virtual void AimedAbility2();

	//	MAX HEALTH IS CHARACTER SPECIFIC
	//const float m_maxHealth = 100.f
	//	OVERRIDE CURRENT HEALTH TO MAXHEALTH ON SPAWN
	float m_currentHealth = 100.f;

	
	static const FName LookNorthBinding;
	static const FName LookEastBinding;
	FVector LookDirection;

	static const FName MoveNorthBinding;
	static const FName MoveEastBinding;
	FVector MoveDirection;
};
