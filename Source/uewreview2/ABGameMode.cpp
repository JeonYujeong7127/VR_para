// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include"MyPawn.h"
#include"ABPlayerController.h"

AABGameMode::AABGameMode()
{
	DefaultPawnClass = AMyPawn::StaticClass();
	PlayerControllerClass = AABPlayerController::StaticClass();
}

void AABGameMode::PostLogin(APlayerController* NewPlayer)
{
	ABLOG(Warning,TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("PostLogin End"));

}

