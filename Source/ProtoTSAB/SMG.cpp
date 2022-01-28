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

	PlayerInputComponent->BindAction("MainFire", IE_Pressed, this, &ASMG::MainFire);
}

/*
void ASMG::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();

				// spawn the projectile
				World->SpawnActor<ASMGBullet>(SpawnLocation, FireRotation);
				ASMGBullet* Projectile = World->SpawnActor<ASMGBullet>(ProjectileClass, SpawnLocation, FireRotation, SpawnParams);
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ASMG::ShotTimerExpired, FireRate);

			bCanFire = false;
		}
	}
}*/

/*
void ASMG::Fire()
{
	// Attempt to fire a projectile.
	if (ProjectileClass)
	{

		// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
		//GunOffset.Set(100.0f, 0.0f, 0.0f);

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle.
			ASMGBullet* Projectile = World->SpawnActor<ASMGBullet>(ProjectileClass, GetActorLocation() , LookDirection.Rotation(), SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = SpawnRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}*/

/*
void ASMG::ShotTimerExpired()
{
	bCanFire = true;
}*/

void ASMG::MainFire()
{
	if (m_world != NULL)
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
	}
}

void ASMG::BeginPlay()
{
	Super::BeginPlay();

	m_world = GetWorld();
}
