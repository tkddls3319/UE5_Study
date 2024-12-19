// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/R1PlayerState.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"	
#include "AbilitySystem/Attributes/R1PlayerSet.h"

AR1PlayerState::AR1PlayerState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UR1AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	PlayerSet = CreateDefaultSubobject<UR1PlayerSet>("PlayerSet");

}

UAbilitySystemComponent* AR1PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UR1AbilitySystemComponent* AR1PlayerState::GetR1AbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UR1PlayerSet* AR1PlayerState::GetR1PlayerSet() const
{
	return PlayerSet;
}
