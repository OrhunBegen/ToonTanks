// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TankCode.generated.h"



UCLASS()
class TOONTANKS_API ATankCode : public ABasePawn
{
	GENERATED_BODY()

	public:

	ATankCode();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditInstanceOnly, Category = "TanksBody")
	float Speed = 700.f;

	UPROPERTY(EditInstanceOnly, Category = "TanksBody")
	float TurnRate = 100.f;

	UFUNCTION(BlueprintCallable)
	void HandleDestruction();
	
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* ArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
	
	void Move(float Value);

	void Turn(float Value);

	

	UPROPERTY()
	APlayerController* TankPlayerController;


};

