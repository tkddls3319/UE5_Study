// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/R1Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "R1Define.h"
#include "Components/WidgetComponent.h"
#include "UI/R1HpBarWidget.h"
// Sets default values
AR1Character::AR1Character()
{
	PrimaryActorTick.bCanEverTick = true;

	HpBarComponent = CreateDefaultSubobject< UWidgetComponent>(TEXT("HealthBar"));
	HpBarComponent->SetupAttachment(GetRootComponent());


	ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/WBP_HpBar.WBP_HpBar_C'"));
	if(HealthBarWidgetClass.Succeeded())
	{
		HpBarComponent->SetWidgetClass(HealthBarWidgetClass.Class);
		HpBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
		HpBarComponent->SetDrawAtDesiredSize(true);
		HpBarComponent->SetRelativeLocation(FVector(0, 0, 100.f));
	}
}

// Called when the game starts or when spawned
void AR1Character::BeginPlay()
{
	Super::BeginPlay();
	RefreshHpBarRatio();
}

// Called every frame
void AR1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AR1Character::HandleGameplayEvent(FGameplayTag EventTag)
{
}

void AR1Character::Highlight()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}

void AR1Character::UnHighlight()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
}

void AR1Character::OnDamaged(int32 Damage, TObjectPtr<AR1Character> Attacker)
{
	Hp = FMath::Clamp(Hp - Damage, 0, MaxHp);
	if (Hp == 0)
	{
		OnDead(Attacker);
	}

	RefreshHpBarRatio();
	D(FString::Printf(TEXT("%d"), Hp));
}

void AR1Character::OnDead(TObjectPtr<AR1Character> Attacker)
{
	if (CreatureState == ECreatureState::Dead)
		return;

	CreatureState = ECreatureState::Dead;
}

void AR1Character::RefreshHpBarRatio()
{
	if (HpBarComponent)
	{
		float Ratio = static_cast<float>(Hp) / MaxHp;

		UR1HpBarWidget* HpBar = Cast<UR1HpBarWidget>(HpBarComponent->GetUserWidgetObject());
		HpBar->SetHpRatio(Ratio);
	}
}

