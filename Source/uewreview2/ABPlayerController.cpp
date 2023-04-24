// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerController.h"

void AABPlayerController::PostInitializeComponents()
{

	ABLOG(Warning, TEXT("ctrler PostInitializing Begin"));
	Super::PostInitializeComponents();
	ABLOG(Warning, TEXT("ctrler PostInitializing End"));
}

void AABPlayerController::OnPossess(APawn* aPawn)
{
	ABLOG(Warning, TEXT("ctrler OnPossess Begin"));
	Super::OnPossess(aPawn);
	ABLOG(Warning, TEXT("ctrler OnPossess End"));
}
