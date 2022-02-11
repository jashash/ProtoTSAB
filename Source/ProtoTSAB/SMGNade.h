// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "SMGNade.generated.h"

UCLASS()
class PROTOTSAB_API ASMGNade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMGNade();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		class UProjectileMovementComponent* ProjectileMovement;

	// Projectile mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		UStaticMeshComponent* ProjectileMeshComponent;

	// Projectile material
	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
		UMaterialInstanceDynamic* ProjectileMaterialInstance;

	UPROPERTY()
		FTimerHandle UnusedHandle;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Explode();

	float m_damageValue = 50.f;
	float m_blastRadius = 500.f;
	int m_fragmentNum = 20;
};
