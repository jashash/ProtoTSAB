// Fill out your copyright notice in the Description page of Project Settings.


#include "SMG.h"

#include "SMGBullet.h"
//#include "Kismet/GameplayStatistics.h"

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

	FireShot(LookDirection);
}

void ASMG::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MainFire", IE_Pressed, this, &ASMG::MainFire);
}


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
}

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
}

void ASMG::ShotTimerExpired()
{
	bCanFire = true;
}

void ASMG::MainFire()
{
	if (m_world != NULL)
	{
		SpawnLocation = GetActorLocation() + GunOffset;

		m_world->SpawnActor<ASMGBullet>(FVector(0.f, 0.f, 200.f), LookDirection.Rotation());

		/*if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}*/
	}
}

void ASMG::BeginPlay()
{
	Super::BeginPlay();

	m_world = GetWorld();
}
