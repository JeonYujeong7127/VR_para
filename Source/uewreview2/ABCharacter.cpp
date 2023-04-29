// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"

// Sets default values
AABCharacter::AABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject< USpringArmComponent>(TEXT("SPRINGARM"));
	camera = CreateDefaultSubobject< UCameraComponent>(TEXT("CAMERA"));

	springArm->SetupAttachment(GetCapsuleComponent());
	camera->SetupAttachment(springArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	springArm->TargetArmLength = 400.0f;
	springArm->SetRelativeRotation(FRotator(100.f, 100.0f, 100.0f));
	springArm->SetRelativeLocation(ArmLocation);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	if (SK_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}


	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("AnimBlueprint'/Game/Book/animation/WarriorAnimBlueprint.WarriorAnimBlueprint_C'"));
	if (WARRIOR_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}


	SetControlMode((int32)EControlMode::GTA);

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.f;
}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABCharacter::SetControlMode(int32 ControlMode)
{
	CurrentControlMode = ControlMode;
	if ((int32)EControlMode::GTA == CurrentControlMode)
	{
		//springArm->TargetArmLength = 450.f;
		//springArm->SetRelativeRotation(FRotator::ZeroRotator);
		ArmLengthTo = 100.f;
		springArm->bUsePawnControlRotation = true;
		springArm->bInheritPitch = true;
		springArm->bInheritRoll = true;
		springArm->bInheritYaw = true;
		springArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	}
	else
	{
		//springArm->TargetArmLength = 800.f;
		//springArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
		ArmLengthTo = 800.f;
		ArmRotationTo = FRotator(-45.f,0.f, 0.f);
		springArm->bUsePawnControlRotation = false;
		//�� �ָ� false ���ѳ��Ƽ� �ؿ� �ֵ��� ��� ���� �ȹ���
		//�ٵ� �׳� �س��°� �����̶� �����ѵ�
		springArm->bInheritPitch = false;
		springArm->bInheritRoll = false;
		springArm->bInheritYaw = false;
		springArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f,720.f,0.f);
	}

	/*
	bUsePawnControlRotation &&bInheritYaw ==1 �� �θ� ī�޶� ��
�����ϰ� ȸ����. �Ƹ� tick �Լ����� ȸ������� �������� �����ϸ鼭
���� �ٲ�°ſ� ī�޶� ����޾Ƽ� �׷���. 
	*/
}


// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	springArm->TargetArmLength = FMath::FInterpTo(springArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	if (CurrentControlMode == (int32)EControlMode::DIABLO)
	{
		springArm->SetRelativeRotation(FMath::RInterpTo(springArm->GetRelativeRotation(), ArmRotationTo, DeltaTime, ArmLengthSpeed));
		if (DirectionToMove.SizeSquared() > 0.f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
	}

}

// Called to bind functionality to input
void AABCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AABCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AABCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("ViewChange"),EInputEvent::IE_Pressed, this, &AABCharacter::ViewChange);

}

void AABCharacter::UpDown(float NewAxisValue)
{
	//ABLOG(Warning, TEXT("pawn UpDown %f"), NewAxisValue);
	//AddMovementInput(GetActorForwardVector(), NewAxisValue);
	//AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);

	if (CurrentControlMode == (int32)EControlMode::GTA)
	{
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
	}
	else if (CurrentControlMode == (int32)EControlMode::DIABLO)
	{
		DirectionToMove.X = NewAxisValue;
	}
}

void AABCharacter::LeftRight(float NewAxisValue)
{
	//ABLOG(Warning, TEXT("pawn LeftRight %f"), NewAxisValue);
	//AddMovementInput(GetActorRightVector(), NewAxisValue);
	//AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
	if (CurrentControlMode == (int32)EControlMode::GTA)
	{
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
	}
	else if (CurrentControlMode == (int32)EControlMode::DIABLO)
	{
		DirectionToMove.Y = NewAxisValue;
	}

}



void AABCharacter::LookUp(float NewAxisValue)
{
	//AddControllerPitchInput(-NewAxisValue);

	if (CurrentControlMode == (int32)EControlMode::GTA)
	{
		AddControllerPitchInput(-NewAxisValue);
	}

}

void AABCharacter::ViewChange()
{
	if (CurrentControlMode == (int32)EControlMode::GTA)
	{
		GetController()->SetControlRotation(GetActorRotation());
		CurrentControlMode = (int32)EControlMode::DIABLO;
	}
	else
	{
		GetController()->SetControlRotation(springArm->GetRelativeRotation());
		CurrentControlMode = (int32)EControlMode::GTA;
	}

	//�̷��͵� �ִµ� ��... �˸� ������� ����
	//CurrentControlMode = CurrentControlMode == EControlMode::GTA ? EControlMode::DIABLO : EControlMode::GTA;
	SetControlMode(CurrentControlMode);
}

void AABCharacter::Turn(float NewAxisValue)
{
	//AddControllerYawInput(NewAxisValue);
	if (CurrentControlMode == (int32)EControlMode::GTA)
	{
		AddControllerYawInput(NewAxisValue);
	}
}