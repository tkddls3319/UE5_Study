// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_FindPatrolPos.h"
#include "AI/R1AIController.h"
#include "Character/R1Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "NavigationSystem.h"

UBTTaskNode_FindPatrolPos::UBTTaskNode_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTaskNode_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn);

	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation OutNextPatrol;
	if (NavSystem->GetRandomPointInNavigableRadius(ControllingPawn->GetActorLocation(), SearchRadius,OUT OutNextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolPosKey.SelectedKeyName, OutNextPatrol);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
