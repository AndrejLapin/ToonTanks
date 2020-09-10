// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}

	RotateTurretFunction(PlayerPawn->GetTargetLocation());
}

void APawnTurret::CheckFireCondition()
{
	// If Player == null || is Dead THEN BAIL!!
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerPawn is missing"));
		return;
	}
	//If Player IS in range THEN FIRE!!
	if (ReturnDistanceToPlayer() <= FireRange && PlayerPawn->GetIsPlayerALive())
	{
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error , TEXT("PlayerPawn is missing"));
		return 0.0f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}


