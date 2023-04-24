// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPawn::PostInitializeComponents()
{
	ABLOG(Warning, TEXT("pawn PostInitializing Begin"));
	Super::PostInitializeComponents();
	ABLOG(Warning, TEXT("pawn PostInitializing End"));
}

void AMyPawn::PossessedBy(AController* pNewController)
{
	ABLOG(Warning, TEXT("pawn PossessedBy Begin"));
	Super::PossessedBy(pNewController);
	ABLOG(Warning, TEXT("pawn PossessedBy End"));
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

