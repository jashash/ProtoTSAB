// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Dummy.generated.h"

UCLASS()
class PROTOTSAB_API ADummy : public APlayerCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADummy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		int DummyType = 0;

	UPROPERTY()
		FTimerHandle MoveHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveUp();
	void MoveDown();

	FVector m_direction;
};
