// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "R1Object.generated.h"

/**
 * 
 */
UCLASS()
class R1_API UR1Object : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int32 Hp = 100;
	UPROPERTY()
	int32 Mp = 200;
	UPROPERTY()
	float Speed = 3.5f;
};
