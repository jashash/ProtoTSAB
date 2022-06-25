// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlayerCharacter.h"
#include "TrainingMode.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTSAB_API ATrainingMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ATrainingMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
		APlayerCharacter* player1;
};
