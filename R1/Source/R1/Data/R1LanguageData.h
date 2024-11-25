// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "R1LanguageData.generated.h"


USTRUCT()
struct FR1LanguageString
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly)
	TArray<FString> Tests;
};

/**
 * 
 */
UCLASS()
class R1_API UR1LanguageData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const TArray<FString> FindFStringByTag(const FGameplayTag& StringTag)const;

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FR1LanguageString> Languages;
};
