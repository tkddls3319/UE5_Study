// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/R1Character.h"
#include "R1Player.generated.h"

DECLARE_DELEGATE(FParsanginDelegate);//파라미터 0
/**
 * 
 */
UCLASS()
class R1_API AR1Player : public AR1Character
{
	GENERATED_BODY()
	
public:
	AR1Player();

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void InitAbilitySystem() override;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void HandleGameplayEvent(FGameplayTag EventTag) override;
	
private:
	UFUNCTION()
	void OnBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;
};
