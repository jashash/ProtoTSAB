// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProtoTSABGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTSAB_API AProtoTSABGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
