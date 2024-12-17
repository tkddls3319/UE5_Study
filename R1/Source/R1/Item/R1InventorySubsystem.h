// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "R1InventorySubsystem.generated.h"

class UR1ItemInstance;
/**
 * 
 */
UCLASS()
class R1_API UR1InventorySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void AddDefaultItem();

	const TArray<TObjectPtr< UR1ItemInstance>>& GetItems() { return Items; }

public:
	UPROPERTY()
	TArray<TObjectPtr<UR1ItemInstance>> Items;
};
