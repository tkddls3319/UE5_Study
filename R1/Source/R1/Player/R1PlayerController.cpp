// Fill out your copyright notice in the Description page of Project Settings.


#include "R1PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "System/R1AssetManager.h"
#include "Data/R1InputData.h"
#include "R1GameplayTags.h"
#include "Character/R1Player.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

AR1PlayerController::AR1PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#pragma region 마우스관련 초기화
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
#pragma endregion
}

void AR1PlayerController::BeginPlay()
{
	Super::BeginPlay();

	//기존 블루프린터 방식
	/*if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}*/

	if (const UR1InputData* InputData = UR1AssetManager::GetAssetByName<UR1InputData>("InputData"))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData->InputMappingContext, 0);
		}
	}

	R1Player = Cast<AR1Player>(GetCharacter());
}

void AR1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (const UR1InputData* InputData = UR1AssetManager::GetAssetByName<UR1InputData>("InputData"))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked< UEnhancedInputComponent>(InputComponent);

		auto Action1 = InputData->FindInputActionByTag(R1GameplayTags::Input_Action_SetDestination);

		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Started, this, &ThisClass::OnInputStarted);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Triggered, this, &ThisClass::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Completed, this, &ThisClass::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Canceled, this, &ThisClass::OnInputStarted);
	}
}

void AR1PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	TickCursorTrace();

	//공격 모션 끝났으면 다시 상태값 초기화
	if (GetCharacter()->GetMesh()->GetAnimInstance()->Montage_IsPlaying(nullptr) == false)
	{
		SetCreatureState(ECreatureState::Moving);
	}

	ChaseTargetAndAttack();
}

void AR1PlayerController::HandleGameplayEvent(FGameplayTag EventTag)
{
	if (EventTag.MatchesTag(R1GameplayTags::Event_Montage_Attack))
	{
		if (TargetActor)
		{
			TargetActor->OnDamaged(R1Player->FinalDamage, R1Player);
		}
	}
}

void AR1PlayerController::TickCursorTrace()
{
	if (bMousePressed)
	{
		return;
	}

	FHitResult OutCursorHit;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT OutCursorHit) == false)
	{
		return;
	}

	AR1Character* LocalHighlightActor = Cast<AR1Character>(OutCursorHit.GetActor());
	if (LocalHighlightActor == nullptr)
	{
		//주시하고있던 액터를 지운다
		if (HighlightActor)
		{
			HighlightActor->UnHighlight();
		}
	}
	else
	{
		if (HighlightActor)
		{
			//기존 액터와 다른 액터라면
			if (HighlightActor != LocalHighlightActor)
			{
				HighlightActor->UnHighlight();
				LocalHighlightActor->Highlight();
			}
		}
		else
		{
			//원래 없었고 새로운 타겟
			LocalHighlightActor->Highlight();
		}
	}

	HighlightActor = LocalHighlightActor;
}

void AR1PlayerController::ChaseTargetAndAttack()
{
	if (TargetActor == nullptr)
	{
		return;
	}

	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}

	FVector Direction = TargetActor->GetActorLocation() - R1Player->GetActorLocation();
	if (Direction.Length() < 250.f)
	{
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Cyan, TEXT("Attack"));

		if (AttackMontage)
		{
			if (bMousePressed)
			{
				/*if(GetCharacter()->GetMesh()->GetAnimInstance()->Montage_IsPlaying(nullptr) == false)*/

				//애니메이션 이벤트 사용전
				//TargetActor->OnDamaged(R1Player->FinalDamage, R1Player);

				FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(R1Player->GetActorLocation(), TargetActor->GetActorLocation());
				R1Player->SetActorRotation(Rotator);

				GetCharacter()->PlayAnimMontage(AttackMontage);
				SetCreatureState(ECreatureState::Skill);

				TargetActor = HighlightActor;
			}
			else
			{
				TargetActor = nullptr;
			}
		}
	}
	else
	{
		FVector WorldDirection = Direction.GetSafeNormal();
		R1Player->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AR1PlayerController::OnInputStarted()
{
	StopMovement();
	bMousePressed = true;
	TargetActor = HighlightActor;//타겟 설정
}

void AR1PlayerController::OnSetDestinationTriggered()
{
	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}
	//무조건 땅을 찍으면 땅으로간다이지만 타겟이 있다면 이동할필요없음
	if (TargetActor)
		return;

	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	if (R1Player)
	{
		FVector WorlDirection = (CachedDestination - R1Player->GetActorLocation()).GetSafeNormal();
		R1Player->AddMovementInput(WorlDirection, 1.0, false);
	}
}

void AR1PlayerController::OnSetDestinationReleased()
{
	bMousePressed = false;

	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}

	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		if (TargetActor == nullptr)
		{
			// We move there and spawn some particles
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
		}
	}

	FollowTime = 0.f;
}

ECreatureState AR1PlayerController::GetCreatureState()
{
	if (R1Player)
	{
		return R1Player->CreatureState;
	}

	return ECreatureState::None;
}

void AR1PlayerController::SetCreatureState(ECreatureState Instate)
{
	if (R1Player)
	{
		R1Player->CreatureState = Instate;
	}
}
