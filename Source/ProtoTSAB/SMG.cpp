// Fill out your copyright notice in the Description page of Project Settings.


#include "SMG.h"

#include "SMGBullet.h"
#include "SMGNade.h"
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

	GunOffset = FVector(80.f, 0.f, 15.f);
	m_currentHealth = m_maxHealth;
}

void ASMG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASMG::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MainFire", IE_Repeat, this, &ASMG::MainFire);
	PlayerInputComponent->BindAction("MainFire", IE_Pressed, this, &ASMG::MainFire);
	PlayerInputComponent->BindAction("AltFire", IE_Pressed, this, &ASMG::AltFire);
	PlayerInputComponent->BindAction("AimedAbility1", IE_Pressed, this, &ASMG::AimedAbility1);
	PlayerInputComponent->BindAction("AimedAbility2", IE_Pressed, this, &ASMG::AimedAbility2);
	PlayerInputComponent->BindAction("RightStickDown", IE_Pressed, this, &ASMG::InitialReload);
}

void ASMG::MainFire()
{
	if (m_world != NULL && m_ammo > 0 && m_canFire && !m_isBlocking)
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

void ASMG::AltFire()
{
	if (m_world != NULL && m_ammo > 0 && !m_isBlocking)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = GetInstigator();

		//	USE THIS LINE FOR AIMED ABILITIES.
		FRotator LookRotation = GetCapsuleComponent()->GetRelativeRotation();

		FVector SpawnLocation = GetActorLocation() + LookRotation.RotateVector(GunOffset);

		//	for loop of ammo going from right to left, all ammo counts have same spread
		if (m_ammo > 1)
		{
			const float CONE_OF_FIRE = 25.f;
			LookRotation.Yaw += CONE_OF_FIRE / 2;
			float interBulletAngle = CONE_OF_FIRE / (m_ammo - 1);
			for (int ii = 0; ii < m_ammo; ++ii)
			{
				ASMGBullet* Bullet = m_world->SpawnActor<ASMGBullet>(SpawnLocation, LookRotation, Params);

				if (Bullet)
				{
					Bullet->FireInDirection((LookRotation).Vector());
					LookRotation.Yaw -= interBulletAngle;
					SpawnLocation = GetActorLocation() + LookRotation.RotateVector(GunOffset);
				}
			}
			m_ammo = 0;
		}
		else
		{
			ASMGBullet* Bullet = m_world->SpawnActor<ASMGBullet>(SpawnLocation, LookRotation, Params);
		}
	}
}

void ASMG::AimedAbility1()
{
	if (m_world != NULL && m_canNade && !m_isBlocking)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = GetInstigator();

		//	USE THIS LINE FOR AIMED ABILITIES.
		const FRotator LookRotation = GetCapsuleComponent()->GetRelativeRotation();

		const FVector SpawnLocation = GetActorLocation() + LookRotation.RotateVector(GunOffset);

		ASMGNade* Grenade = m_world->SpawnActor<ASMGNade>(SpawnLocation, LookRotation, Params);

		Grenade->FireInDirection(LookRotation.Vector());
		
		m_canNade = false;
		GetWorldTimerManager().SetTimer(NadeHandle, this, &ASMG::ResetAimedAbility1, m_nadeCooldown, false);
	}
}

void ASMG::AimedAbility2()
{
	if (m_canDash && !m_isBlocking)
	{
		GetCharacterMovement()->BrakingFrictionFactor = 0.f;
		LaunchCharacter(MoveDirection.GetSafeNormal() * m_dashDistance, true, true);
		m_canDash = false;
		GetWorldTimerManager().SetTimer(DashHandle, this, &ASMG::StopAimedAbility2, m_dashStop, false);
	}
}

void ASMG::InitialReload()
{
	if (!m_isBlocking)
	{
		m_canFire = false;
		GetWorldTimerManager().SetTimer(ReloadHandle, this, &ASMG::AbleToFire, m_reloadCooldown, false);
	}
}

void ASMG::AbleToFire()
{
	m_ammo = 10;
	m_canFire = true;
}

void ASMG::ResetAimedAbility1()
{
	m_canNade = true;
}

void ASMG::StopAimedAbility2()
{
	GetCharacterMovement()->StopMovementImmediately();
	GetWorldTimerManager().SetTimer(DashHandle, this, &ASMG::ResetAimedAbility2, m_dashCooldown, false);
	GetCharacterMovement()->BrakingFrictionFactor = 2.f;
}

void ASMG::ResetAimedAbility2()
{
	m_canDash = true;
}

void ASMG::BeginPlay()
{
	Super::BeginPlay();

	m_world = GetWorld();
}
