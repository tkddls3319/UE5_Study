// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "R1AssetData.generated.h"

USTRUCT()
struct FAssetEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FName AssetName;

	UPROPERTY(EditDefaultsOnly)
	FSoftObjectPath AssetPath;//경로설정하는거

	UPROPERTY(EditDefaultsOnly)
	TArray<FName> AssetLabels;

};

USTRUCT()
struct FAssetSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAssetEntry> AssetEntries;
};

/**
 * 
 */
UCLASS()
class R1_API UR1AssetData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	//실제로 캐싱하는 부분 PreSave 함수는 Unreal Engine의 에디터 환경에서 객체가 저장되기 직전에 호출됩니다.
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;
	
public:
	////PreSave에서 캐싱한 데이터에서 이름과 라벨로 찾기위한 함수
	FSoftObjectPath GetAssetPathByName(const FName& AssetName);
	const FAssetSet& GetAssetSetByLabel(const FName& Label);

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, FAssetSet> AssetGroupNameToSet;

	UPROPERTY()
	TMap<FName, FSoftObjectPath> AssetNameToPath;//PreSave에서 캐싱한 데이터 담을 변수

	UPROPERTY()
	TMap<FName, FAssetSet> AssetLabelToSet;//PreSave에서 캐싱한 데이터 담을 변수
};
