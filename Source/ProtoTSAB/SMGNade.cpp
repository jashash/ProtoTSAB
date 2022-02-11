// Fill out your copyright notice in the Description page of Project Settings.


#include "SMGNade.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "SMGFragment.h"
#include "PlayerCharacter.h"

// Sets default values
ASMGNade::ASMGNade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionSphere)
	{
		// Use a sphere as a simple collision representation.
		CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius.
		CollisionSphere->InitSphereRadius(1.f);
		CollisionSphere->SetSimulatePhysics(true);
		// Set the root component to be the collision component.
		RootComponent = CollisionSphere;
	}
	if (!ProjectileMovement)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovement->SetUpdatedComponent(CollisionSphere);
		ProjectileMovement->InitialSpeed = 1000.0f;
		ProjectileMovement->MaxSpeed = 1000.0f;
		ProjectileMovement->bRotationFollowsVelocity = true;
		ProjectileMovement->bShouldBounce = true;
		//	***************I WANT IT TO BOUNCE*************************
		ProjectileMovement->ProjectileGravityScale = 0.f;
	}
	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Meshes/Sphere.Sphere'"));
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}
		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/Meshes/Fbx_Default_Material.Fbx_Default_Material'"));
		if (Material.Succeeded())
		{
			ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
		}
		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}
	InitialLifeSpan = 2.f;

}

// Called every frame
void ASMGNade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASMGNade::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
}

// Called when the game starts or when spawned
void ASMGNade::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ASMGNade::Explode, 1.9f, false);
}

void ASMGNade::Explode()
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();

	FRotator LookRotation = FRotator(1.f, 0.f, 0.f);

	FVector SpawnLocation = GetActorLocation() + LookRotation.RotateVector(FVector(80.f, 0.f, 15.f));

	for (int ii = 0; ii < m_fragmentNum; ++ii)
	{
		ASMGFragment* frag = GetWorld()->SpawnActor<ASMGFragment>(SpawnLocation, LookRotation, Params);

		if (frag)
		{
			frag->FireInDirection((LookRotation).Vector());
			LookRotation.Yaw -= 360.f / m_fragmentNum;
			SpawnLocation = GetActorLocation() + LookRotation.RotateVector(FVector(80.f, 0.f, 15.f));
		}
	}
}

