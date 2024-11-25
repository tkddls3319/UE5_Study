// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/R1LanguageData.h"

const TArray<FString> UR1LanguageData::FindFStringByTag(const FGameplayTag& StringTag) const
{
	for (const FR1LanguageString& string : Languages)
	{
		if (string.InputTag == StringTag) {
			return string.Tests;
		}
	}

	return TArray<FString>();
}
