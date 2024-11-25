// Fill out your copyright notice in the Description page of Project Settings.


#include "R1PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "System/R1AssetManager.h"
#include "Data/R1InputData.h"
#include "Data/R1LanguageData.h"
#include "R1GameplayTags.h"

AR1PlayerController::AR1PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AR1PlayerController::BeginPlay()
{
	Super::BeginPlay();

	//기존 블루프린터 방식
	/*if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}*/

	if (const UR1InputData* InputData = UR1AssetManager::GetAssetByName<UR1InputData>("InputData"))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData->InputMappingContext, 0);
		}
	}

	if (const UR1LanguageData* LanguageData = UR1AssetManager::GetAssetByName<UR1LanguageData>("LanguageData"))
	{
		TArray<FString> strings = LanguageData->FindFStringByTag(R1GameplayTags::Test_String_Korea);

		for (const auto& item : strings)
		{
			UE_LOG(LogR1, Log, TEXT("%s"), *item);
		}
	}
}

void AR1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (const UR1InputData* InputData = UR1AssetManager::GetAssetByName<UR1InputData>("InputData"))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked< UEnhancedInputComponent>(InputComponent);

		auto Action1 = InputData->FindInputActionByTag(R1GameplayTags::Input_Action_Move);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);

		auto Action2 = InputData->FindInputActionByTag(R1GameplayTags::Input_Action_Turn);
		EnhancedInputComponent->BindAction(Action2, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);
	}

	//기존 블루프린터 방식
	//if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	//{
	//	EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Test);
	//	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	//	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);
	//}

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
