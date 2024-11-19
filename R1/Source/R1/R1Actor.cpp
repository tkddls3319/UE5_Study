// Fill out your copyright notice in the Description page of Project Settings.


#include "R1Actor.h"
#include "R1Object.h"
//#include "Components/StaticMeshComponent.h"
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

}

// Called every frame
void AR1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

