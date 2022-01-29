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

	GunOffset = FVector(50.f, 0.f, 15.f);
	FireRate = 0.1f;
	m_currentHealth = m_maxHealth;
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
	PlayerInputComponent->BindAction("MainFire", IE_Pressed, this, &ASMG::MainFire);
	PlayerInputComponent->BindAction("AltFire", IE_Pressed, this, &ASMG::AltFire);
	PlayerInputComponent->BindAction("AimedAbility1", IE_Pressed, this, &ASMG::AimedAbility1);
	PlayerInputComponent->BindAction("Offense", IE_Pressed, this, &ASMG::Reload);
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

void ASMG::AltFire()
{
	if (m_world != NULL && m_ammo > 0)
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
	if (m_world != NULL)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = GetInstigator();

		//	USE THIS LINE FOR AIMED ABILITIES.
		const FRotator LookRotation = GetCapsuleComponent()->GetRelativeRotation();

		const FVector SpawnLocation = GetActorLocation() + LookRotation.RotateVector(GunOffset);

		ASMGNade* Grenade = m_world->SpawnActor<ASMGNade>(SpawnLocation, LookRotation, Params);

		if (Grenade)
		{
			Grenade->FireInDirection(LookRotation.Vector());
		}
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
