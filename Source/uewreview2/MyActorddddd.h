// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "uewreview2.h"
#include "GameFramework/Actor.h"
#include "MyActorddddd.generated.h"


UCLASS()
class UEWREVIEW2_API AMyActorddddd : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActorddddd();
	//hello


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
