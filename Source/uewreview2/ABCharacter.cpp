// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"

// Sets default values
AABCharacter::AABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject< USpringArmComponent>(TEXT("SPRINGARM"));
	camera = CreateDefaultSubobject< UCameraComponent>(TEXT("CAMERA"));
	glider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GLIDER"));
	light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));

	springArm->SetupAttachment(GetCapsuleComponent());
	camera->SetupAttachment(springArm);
	glider->SetupAttachment(GetCapsuleComponent());
	light->SetupAttachment(GetCapsuleComponent());
	light->SetLightBrightness(50);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BODY(TEXT("StaticMesh'/Game/Book/glider/Hang_gliding_3.Hang_gliding_3'"));
	if (SM_BODY.Succeeded())
	{
		glider->SetStaticMesh(SM_BODY.Object);
	}
	// ī�޶� ��ġ
	springArm->TargetArmLength = 400.0f;
	springArm->SetRelativeRotation(FRotator(0,0,0));
	springArm->SetRelativeLocation(ArmLocation);
	// �۶��̴� �۾�
	glider->SetRelativeLocation(FVector(30, 0.f, 170.f));
	glider->SetRelativeRotation(FRotator(0,-90,30));
	light->SetRelativeLocation(FVector(0.f, 0.f, 50.f));


	/////////////
	GetMesh()->SetRelativeLocationAndRotation(FVector(.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("SkeletalMesh'/Game/Book/animation/ds.ds'"));
	//if (SK_CARDBOARD.Succeeded())
	//{
	//	ABLOG(Warning, TEXT("why dont "));
	//	GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	//}


	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	//static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("AnimBlueprint'/Game/Book/animation/ds_Skeleton_AnimBlueprint1.ds_Skeleton_AnimBlueprint1_C'"));
	//if (WARRIOR_ANIM.Succeeded())
	//{
	//	GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	//}


	SetControlMode((int32)EControlMode::GLIDER);

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
		springArm->bInheritPitch = false;
		springArm->bInheritRoll = false;
		springArm->bInheritYaw = false;
		springArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	}
	else if ((int32)EControlMode::GLIDER == CurrentControlMode)
	{
		ArmLengthTo = 0.f;
		springArm->bUsePawnControlRotation = true;
		springArm->bInheritPitch = true;
		springArm->bInheritRoll = false;
		springArm->bInheritYaw = true;
		springArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationPitch = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
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
	else
	{
		AddMovementInput(GetActorForwardVector(), NewAxisValue);

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
	else
	{

		AddMovementInput(GetActorRightVector(), NewAxisValue);
	}

}



void AABCharacter::LookUp(float NewAxisValue)
{
	//AddControllerPitchInput(-NewAxisValue);

	if (CurrentControlMode != (int32)EControlMode::DIABLO)
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
	else if(CurrentControlMode == (int32)EControlMode::DIABLO)
	{
		GetController()->SetControlRotation(springArm->GetRelativeRotation());
		CurrentControlMode = (int32)EControlMode::GLIDER;
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
	if (CurrentControlMode != (int32)EControlMode::DIABLO)
	{
		AddControllerYawInput(NewAxisValue);
	}
}