// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "R1PlayerController.generated.h"

class UNiagaraSystem;
struct FInputActionValue;
UCLASS()
class R1_API AR1PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AR1PlayerController(const FObjectInitializer& ObjectInitializer );

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
#pragma region 마우스관련
	//마우스 행동 함수
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
#pragma endregion
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold = 0.3f;//마우스가 누르는 시간정의 0.3이상이면 누른방향으로 계속이동

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UNiagaraSystem> FXCursor;//마우스 커서

private:
	FVector CachedDestination; //마우스 누른 위치
	float FollowTime;//마우스 눌린시간
};
