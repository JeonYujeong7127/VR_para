// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	capsule = CreateDefaultSubobject< UCapsuleComponent>(TEXT("CAPSULE"));
	mesh = CreateDefaultSubobject< USkeletalMeshComponent>(TEXT("MESH"));
	movement = CreateDefaultSubobject< UFloatingPawnMovement>(TEXT("MOVEMENT"));
	springArm = CreateDefaultSubobject< USpringArmComponent>(TEXT("SPRINGARM"));
	camera = CreateDefaultSubobject< UCameraComponent>(TEXT("CAMERA"));

	RootComponent = capsule;
	mesh->SetupAttachment(capsule);
	springArm->SetupAttachment(capsule);
	camera->SetupAttachment(springArm);

	capsule->SetCapsuleHalfHeight(88.0f);
	capsule->SetCapsuleRadius(34.f);
	mesh->SetRelativeLocationAndRotation(FVector(.0f, 0.0f, -88.0f),FRotator(0.0f,-90.0f,0.0f));
	springArm->TargetArmLength = 400.0f;
	springArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	if (SK_CARDBOARD.Succeeded())
	{
		mesh->SetSkeletalMesh(SK_CARDBOARD.Object);
	}


}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	UAnimationAsset* AnimAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("AnimSequence'/Game/Book/animation/WarriorRun.WarriorRun'"));
	if (AnimAsset != nullptr)
	{
		mesh->PlayAnimation(AnimAsset, true);
	}
	
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
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyPawn::LeftRight);

}

void AMyPawn::UpDown(float NewAxisValue)
{
	ABLOG(Warning, TEXT("pawn UpDown %f"),NewAxisValue);
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void AMyPawn::LeftRight(float NewAxisValue)
{
	ABLOG(Warning, TEXT("pawn LeftRight %f"), NewAxisValue);
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}

