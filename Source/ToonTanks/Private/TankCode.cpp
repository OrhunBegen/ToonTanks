// Fill out your copyright notice in the Description page of Project Settings.


#include "TankCode.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATankCode::ATankCode()
{
	ArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	ArmComponent -> SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera -> SetupAttachment(ArmComponent);
}

//called when the game starts or when spawned
void ATankCode::BeginPlay() 
{

	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());

	
}

// Called every frame
void ATankCode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if(TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController-> GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		
		RotateTurret(HitResult.ImpactPoint);
		DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10.f , 12, FColor::Red,false, 0.1f);
	}
}

void ATankCode::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent-> BindAxis(TEXT("MoveForward"), this, &ATankCode::Move);
	PlayerInputComponent-> BindAxis(TEXT("Turn"), this, &ATankCode::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed,this, &ATankCode::Fire);

	
}
void ATankCode::Move (float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Forward or Backwards %f"), Value);
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);;
	AddActorLocalOffset(DeltaLocation, true);
}
void ATankCode::Turn (float Value)
{
	//UE_LOG(LogTemp, Warning , TEXT("Turn %f"), Value);
	FRotator DeltaRotation = FRotator::ZeroRotator;

	// Yaw= value * Turn Rate * delta time
	DeltaRotation.Yaw = Value* TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation,true);
}

void ATankCode::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	
}