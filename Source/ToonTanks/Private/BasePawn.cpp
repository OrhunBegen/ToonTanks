// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(("Capsule Collider"));
	RootComponent = CapsuleComponent;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh-> SetupAttachment(CapsuleComponent);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh-> SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint -> SetupAttachment(TurretMesh);
	
}

void ABasePawn::HandleDestruction(){

	//Visual/sound Effects

	if(DeathEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathEffect, GetActorLocation(), GetActorRotation());
	}
	
	

}

void ABasePawn::RotateTurret(const FVector& LookAtTarget) const
{
	FVector const ToTarget = LookAtTarget - TurretMesh-> GetComponentLocation();

	const FRotator LookAtRotation =FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

    	//TurretMesh -> SetWorldRotation(LookAtRotation);

	TurretMesh -> SetWorldRotation(FMath::RInterpTo
		(TurretMesh -> GetComponentRotation(),
		LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		8.f));	
}

void ABasePawn::Fire()
{
	//DrawDebugSphere(GetWorld(), ProjectileSpawnPoint -> GetComponentLocation(),	10.f, 12, FColor::Red, false, 3.f);

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass , ProjectileSpawnPoint->GetComponentLocation() , ProjectileSpawnPoint->GetComponentRotation() );
	Projectile -> SetOwner(this);

}
