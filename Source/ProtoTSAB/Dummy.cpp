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
}

// Called every frame
void ADummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called when the game starts or when spawned
void ADummy::BeginPlay()
{
	Super::BeginPlay();
	
}

