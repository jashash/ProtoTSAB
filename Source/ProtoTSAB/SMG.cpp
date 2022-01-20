// Fill out your copyright notice in the Description page of Project Settings.


#include "SMG.h"

ASMG::ASMG()
	:APlayerCharacter()
{

	GunOffset = FVector(90.f, 0.f, 0.f);
	CanFire = true;
}

void ASMG::MainFire()
{
	/*
	// If it's ok to fire again
	if (CanFire == true)
	{
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = GetActorLocation() + GunOffset;

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			// spawn the projectile
			World->SpawnActor<ATwinStickTestProjectile>(SpawnLocation, FireRotation);
		}

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ATwinStickTestPawn::ShotTimerExpired, FireRate);

		// try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		bCanFire = false;
	}
	*/
}
