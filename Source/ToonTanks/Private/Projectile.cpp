// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));

	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	ProjectileMovementComponent->InitialSpeed = 200.f;
	ProjectileMovementComponent->MaxSpeed = 200.f;

	TrailParticles =	CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));

	TrailParticles ->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}

}




// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	AActor* MyOwner = GetOwner();
	if(MyOwner == nullptr)
	{
		Destroy();
		return;
		
	}
	APawn* MyOwnerInstigator = MyOwner->GetInstigator();
	UClass* DamageTypeClass = UDamageType::StaticClass();
	if( OtherActor && OtherActor != this && OtherActor != MyOwner && MyOwnerInstigator != OtherActor)
	{
		UGameplayStatics::ApplyDamage( OtherActor, Damage, MyOwnerInstigator->GetController(), this, DamageTypeClass);	

		if(HitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());	
		}
		if(HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(HitCameraShakeClass);
		}
		
		
		//UE_LOG(LogTemp, Warning, TEXT("Projectile Hit %s"), *OtherActor->GetName());
	}
	else if(OtherActor == MyOwner)
	{
		Destroy();
	}
	Destroy();
}
  
