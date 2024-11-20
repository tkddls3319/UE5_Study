// Fill out your copyright notice in the Description page of Project Settings.


#include "MainActor.h"
#include "R1Actor.h"
// Sets default values
AMainActor::AMainActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AR1Actor> FindClass(TEXT("/Script/Engine.Blueprint'/Game/_Sangin/BP_R1Actor.BP_R1Actor_C'"));
	if (FindClass.Succeeded())
	{
		ActorClass = FindClass.Class;
	}


}

// Called when the game starts or when spawned
void AMainActor::BeginPlay()
{
	Super::BeginPlay();

	FVector Location(0, 0, 0);
	FRotator Rotation(0, 0, 0);


	//c++로만든 actor 호출
	{
		//Actor = GetWorld()->SpawnActor<AR1Actor>(Location, Rotation);
		//Actor->SetLifeSpan(5.0f);//5초후 액터 제거
		//GetWorld()->DestroyActor(Actor);//즉시 액터 제거
	}

	{
		//ActorClass 생성
		Actor = Cast<AR1Actor>(GetWorld()->SpawnActor(ActorClass));
		//Actor->SetLifeSpan(5.0f);//5초후 액터 제거
	}
}

// Called every frame
void AMainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

