// Fill out your copyright notice in the Description page of Project Settings.


#include "R1PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
AR1PlayerController::AR1PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AR1PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AR1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Test);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);
	}

}
void AR1PlayerController::Input_Test(const FInputActionValue& InputValue) 
{
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Cyan, TEXT("TEST"));
}

void AR1PlayerController::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	if (MovementVector.X != 0)
	{
		//AddActorWorldOffset 해당버전은 직접적으로 월드좌표를 이용하여 움직인다. 이 때 대각선같은 부분에 대한 연산은 따로 만들어줘야한다.
		/*FVector Direction = FVector::ForwardVector * MovementVector.X;
		GetPawn()->AddActorWorldOffset(Direction * 50.0f);*/

		/*
		Unreal Engine에서 **AddMovementInput**와 Movement(정확히는 CharacterMovementComponent)는 서로 관련이 깊다.
		AddMovementInput은 캐릭터의 입력을 처리하여 이동 방향을 설정하는 함수이고, 
		이동은 **CharacterMovementComponent**가 실제로 처리합니다.
		즉 AddMovementInput는 입력을 이동 방향 벡터로 변환하여 캐릭터의 이동 명령을 예약하는 함수입니다.
		CharacterMovementComponent는 예약된 이동 명령을 처리하는 컴포넌트이다.
		*/
		FRotator Rotator = GetControlRotation();//PlayerController에 입력된 방향
		FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.X);
	}
	if (MovementVector.Y != 0)
	{
	/*	FVector Direction = FVector::ForwardVector * MovementVector.Y;
		GetPawn()->AddActorWorldOffset(Direction * 50.0f);*/

		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.Y);
	}

}

void AR1PlayerController::Input_Turn(const FInputActionValue& InputValue)
{
	float Val = InputValue.Get<float>();
	AddYawInput(Val);//연구적으로 로테이션의 상태가 PlayerController에 보존된다.
}
