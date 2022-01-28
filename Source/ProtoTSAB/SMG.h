// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "SMG.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTSAB_API ASMG : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	ASMG();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;

	/* How fast the weapon will fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float FireRate;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class UClass> ProjectileClass;

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;
	*/

	class UWorld* m_world;

protected:
	virtual void BeginPlay() override;

	virtual void MainFire() override;

	void Reload();

	int m_ammo = 10;
};
