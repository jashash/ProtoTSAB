// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Runtime/Engine/Public/TimerManager.h"
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

	UPROPERTY()
		FTimerHandle ReloadHandle;
	UPROPERTY()
		FTimerHandle DashHandle;
	UPROPERTY()
		FTimerHandle NadeHandle;

	class UWorld* m_world;

protected:
	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;

	/* How fast the weapon will fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float FireRate;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class UClass> ProjectileClass;

	virtual void BeginPlay() override;
	virtual void MainFire() override;	//	peashooter
	virtual void AltFire() override;	//	shotgun remaining ammo
	virtual void AimedAbility1() override;	//	grenade
	virtual void AimedAbility2() override;	//	dash

	void InitialReload();
	void AbleToFire();

	void ResetAimedAbility1();

	void StopAimedAbility2();
	void ResetAimedAbility2();


	const float m_maxHealth = 100.f;

	int m_ammo = 10;
	bool m_canFire = true;
	float m_reloadCooldown = 0.5f;

	bool m_canNade = true;
	float m_nadeCooldown = 2.f;

	bool m_canDash = true;
	float m_dashStop = 0.08f;
	float m_dashDistance = 6000.f;
	float m_dashCooldown = 1.f;
};
