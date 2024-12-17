#pragma once

UENUM(BlueprintType)
enum class ECreatureState : uint8
{
	None,
	Moving,
	Skill,
	Dead,
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Junk, 
	Poor,
	Common,
	Uncommon,
	Rare, 
	Epic,
	Legendary,
	Unique,
	Count UMETA(Hidden)
};

#define D(x) if(GEngine) {GEngine -> AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, x);}