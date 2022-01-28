// Fill out your copyright notice in the Description page of Project Settings.


#include "SMG.h"

#include "SMGBullet.h"
//#include "Kismet/GameplayStatistics.h"
#include "UObject/Class.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "TrainingMode.h"

ASMG::ASMG()
	:APlayerCharacter()
{

	GunOffset = FVector(50.f, 0.f, 50.f);
	FireRate = 0.1f;
}

void ASMG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FireShot(LookDirection);
}

void ASMG::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MainFire", IE_Repeat, this, &ASMG::MainFire);
	PlayerInputComponent->BindAction("Thought", IE_Pressed, this, &ASMG::Reload);
}

void ASMG::MainFire()
{
	if (m_world != NULL && m_ammo > 0)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = GetInstigator();

		//	USE THIS LINE FOR AIMED ABILITIES.
		const FRotator LookRotation = GetCapsuleComponent()->GetRelativeRotation();

		const FVector SpawnLocation = GetActorLocation() + LookRotation.RotateVector(GunOffset);

		ASMGBullet* Bullet = m_world->SpawnActor<ASMGBullet>(SpawnLocation, LookRotation, Params);

		if (Bullet)
		{
			Bullet->FireInDirection(LookRotation.Vector());
		}
		--m_ammo;
	}
}

void ASMG::Reload()
{
	m_ammo = 10;
}

void ASMG::BeginPlay()
{
	Super::BeginPlay();

	m_world = GetWorld();
}
