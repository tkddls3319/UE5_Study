// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/R1Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/R1PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AR1Player::AR1Player()
{
	//캐릭터가 카메라 회전에 의해 MoveMentController에 영향을 받지 않게
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	//캐릭터가 이동할 때 MoveMentController의 회전값으로 변경
	GetCharacterMovement()->bOrientRotationToMovement = true;

	//어느 속도로 MoveMentController 회전값으로 이동할지
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->bInheritYaw = false;//이거 지우면 클릭한방향으로 돌아감

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;//카메라가 캐릭터가 회전할 때 함께 회전하지 않도록 고정

	SpringArm->TargetArmLength = 800.0f;
	SpringArm->SetRelativeRotation(FRotator(-60, 0, 0));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
}

void AR1Player::BeginPlay()
{
	Super::BeginPlay();
}

void AR1Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
