// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "uewreview2.h"
#include "GameFramework/Character.h"
#include "NiagaraComponent.h"
#include "ABCharacter.generated.h"

UCLASS()
class UEWREVIEW2_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum class EControlMode
	{
		GTA,
		DIABLO,
		GLIDER,
	};


	void SetControlMode(int32 mode);

	UPROPERTY(EditAnywhere, Category = Mode)
		int32 CurrentControlMode;
	FVector DirectionToMove = FVector::ZeroVector;

	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 500.0f;
	FVector ArmLocation = FVector(50.f,0,100.f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = SpringArm)
		USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* camera;
	UPROPERTY(VisibleAnywhere, Category = Glider)
		UStaticMeshComponent* glider;
	UPROPERTY(VisibleAnywhere, Category = Light)
		UPointLightComponent* light;
	UPROPERTY(VisibleAnywhere, Category = Sound)
		UAudioComponent* windsound;

	UPROPERTY(VisibleAnywhere, Category = Particle)
		UParticleSystemComponent* windPtc;


	UPROPERTY(VisibleAnywhere, Category = Particle)
		UParticleSystemComponent* windPtc2;


	UPROPERTY(VisibleAnywhere, Category = Particle)
		UNiagaraSystem* windNia;
	
private:

	UPROPERTY(Category = Sound, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USoundBase* WindSoundBase;
	
	



private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void Turn(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void ViewChange();
};
