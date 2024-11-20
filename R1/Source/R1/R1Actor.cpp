// Fill out your copyright notice in the Description page of Project Settings.


#include "R1Actor.h"
#include "R1Object.h"
//#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
AR1Actor::AR1Actor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	if (Box != nullptr)
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> FindMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Sangin/SM_ChamferCube.SM_ChamferCube'"));

		if (FindMesh.Succeeded())
		{
			Box->SetStaticMesh(FindMesh.Object);
		}
	}
}

// Called when the game starts or when spawned
void AR1Actor::BeginPlay()
{
	Super::BeginPlay();

	//월드내에 AR1Actor의 액터 찾아오기
	{
		Target = UGameplayStatics::GetActorOfClass(GetWorld(), AR1Actor::StaticClass());
	}

	//테그를 사용하여 모든 테그 가져오기
	{
	/*	TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Target"), Actors);

		if (Actors.Num() > 0)
		{
			Target = Actors[0];
		}*/
	}

}

// Called every frame
void AR1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target != nullptr)
	{
		float Speed = 1.f;
		float Distance = DeltaTime * Speed;

		FVector Location = GetActorLocation();//현재 Actor위치

		FVector DirectionVector = Target->GetActorLocation() - Location;
		//DirectionVector.Length(); // 남은거리
		//DirectionVector.Normalize();// 방향

		// 내위치와 방향백터와 거리를 이용해 목적 백터 생성
		{
			//FVector NewLocation = Location + FVector::ForwardVector * Distance;
			//SetActorLocation(NewLocation);//위치 변경
		}

		// 방향백터만 넣으면 위치변경 현재 내위치는 알아서 구해줌
		{
			AddActorWorldOffset(DirectionVector * Distance);
		}
	}
}

