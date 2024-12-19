// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/R1AbilitySystemComponent.h"

void UR1AbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& StartupAbilities)
{
	for (auto& AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);//런타임에 스킬을 관리
		FGameplayAbilitySpecHandle SpecHandle = GiveAbility(AbilitySpec);//실제로 스킬배워서 사용할 수 있음

		auto& a = ActivatableAbilities;

		//TryActivateAbility(SpecHandle);//한 번 사용
		//GiveAbilityAndActivateOnce(AbilitySpec);//부여하자마자 사용

		SpecHandles.Add(SpecHandle);// Handle 사용
	}
}

void UR1AbilitySystemComponent::ActivateAbility(FGameplayTag AbilityTag)
{
	for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandles)
	{
		// TODO
		TryActivateAbility(SpecHandle);
	}
}
