// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/R1AnimInstance.h"

UR1AnimInstance::UR1AnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UR1AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UR1AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
