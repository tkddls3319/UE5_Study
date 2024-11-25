// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "R1PlayerController.generated.h"

struct FInputActionValue;
UCLASS()
class R1_API AR1PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AR1PlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Turn(const FInputActionValue& InputValue);

protected:

	//앞으로 AssetManager에서 AssetData와 InputData를 활용하여 LOAD하여사용할거
	//UPROPERTY(EditAnywhere, Category = Input)
	//TObjectPtr<class UInputMappingContext> InputMappingContext;

	//UPROPERTY(EditAnywhere, Category = Input)
	//TObjectPtr<class UInputAction> TestAction;

	//UPROPERTY(EditAnywhere, Category = Input)
	//TObjectPtr<class UInputAction> MoveAction;

	//UPROPERTY(EditAnywhere, Category = Input)
	//TObjectPtr<class UInputAction> TurnAction;

};
