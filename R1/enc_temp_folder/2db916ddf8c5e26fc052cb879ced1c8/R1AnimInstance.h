// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "R1AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class R1_API UR1AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UR1AnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
