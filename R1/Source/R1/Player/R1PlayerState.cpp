// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/R1PlayerState.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"	


AR1PlayerState::AR1PlayerState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UR1AbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	
}

UAbilitySystemComponent* AR1PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
