// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "R1PlayerState.generated.h"

class UR1AbilitySystemComponent;
class UR1PlayerSet;
/**
 * 
 */
UCLASS()
class R1_API AR1PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AR1PlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
public:
	// IAbilitySystemInterface을(를) 통해 상속됨
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UR1AbilitySystemComponent* GetR1AbilitySystemComponent() const;
	UR1PlayerSet* GetR1PlayerSet() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UR1AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UR1PlayerSet> PlayerSet;
};
