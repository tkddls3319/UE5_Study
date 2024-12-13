// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/R1AIController.h"
#include "Navigation/PathFollowingComponent.h"
AR1AIController::AR1AIController(const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{

}

void AR1AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AR1AIController::BeginPlay()
{
	Super::BeginPlay();
	
	//FVector Dest = { 0,0,0 };
	//FAIMoveRequest MoveRequest;
	//MoveRequest.SetGoalLocation(Dest);//목적지
	//MoveRequest.SetAcceptanceRadius(15.f);//거리 15만큼 이면 도착했다고 인정

	//FNavPathSharedPtr NavPath;// 경로 로그를 위해
	//MoveTo(MoveRequest, OUT& NavPath);

	////로그 찍는 디버그 코드
	//if (NavPath.IsValid())
	//{
	//	TArray<FNavPathPoint>& PathPoints =  NavPath->GetPathPoints();
	//	
	//	for (const auto& Point : PathPoints )
	//	{
	//		const FVector& Location = Point.Location;
	//		DrawDebugSphere(GetWorld(), Location, 12.f, 12, FColor::Green, false, 10.0f);
	//	}
	//}
}

void AR1AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
