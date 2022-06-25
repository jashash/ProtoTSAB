// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

UENUM(BlueprintType)
enum class ECharacter : uint8
{
	VE_Default	UMETA(DisplayName = "Dummy"),
	VE_SMG		UMETA(DisplayName = "SMG")
};

/**
 * 
 */
UCLASS()
class PROTOTSAB_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
		ECharacter characterClass;
};
