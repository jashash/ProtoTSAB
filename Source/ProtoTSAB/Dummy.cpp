// Fill out your copyright notice in the Description page of Project Settings.


#include "Dummy.h"

#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"

// Sets default values
ADummy::ADummy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//m_currentHealth = m_maxHealth;

	m_direction = FVector(1.f, 0, 0);
}

// Called every frame
void ADummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DummyType == 1)
	{
		AddMovementInput(m_direction, 1.f);
	}
}

// Called when the game starts or when spawned
void ADummy::BeginPlay()
{
	Super::BeginPlay();
	
	if (DummyType == 1)
	{
		MoveDown();
	}
}

void ADummy::MoveUp()
{
	m_direction = FVector(1.f, 0, 0);
	GetWorldTimerManager().SetTimer(MoveHandle, this, &ADummy::MoveDown, 2.f, false);
}

void ADummy::MoveDown()
{
	m_direction = FVector(-1.f, 0, 0);
	GetWorldTimerManager().SetTimer(MoveHandle, this, &ADummy::MoveUp, 2.f, false);
}

