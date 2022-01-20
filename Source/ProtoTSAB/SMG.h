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

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

protected:

	virtual void MainFire() override;
	bool CanFire = true;
};
