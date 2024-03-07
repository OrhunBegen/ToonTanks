// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "TankCode.h"
#include "Kismet/GameplayStatics.h"


//called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
                                                                                     	
	}
	

	



void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Tank = Cast<ATankCode>(UGameplayStatics::GetPlayerPawn(this, 0));


		
	if(Tank)
	{
		//find the distance to the tank
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		//check to see if the tank is in range
		if (Distance <=FireRange)
		{                                                                              	
			//rotate the turret to face the tank
			RotateTurret(Tank->GetActorLocation());
		}
	}

	
	
		
}