// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeToonTanks.h"

#include "TankCode.h"
#include "Kismet/GameplayStatics.h"
#include "Turret.h"


void AGameModeToonTanks::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank -> HandleDestruction();
		if ( Tank -> GetTankPlayerController())
		{
			Tank -> DisableInput(Tank -> GetTankPlayerController());
			Tank -> GetTankPlayerController() -> bShowMouseCursor = false;
			
		}
	
	}
	else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
	{
		DestroyedTurret -> HandleDestruction();
	}
	
	
}
void AGameModeToonTanks::BeginPlay()
{
	Super::BeginPlay();
	
	Tank = Cast <ATankCode>(UGameplayStatics::GetPlayerPawn(this, 0));
	
}