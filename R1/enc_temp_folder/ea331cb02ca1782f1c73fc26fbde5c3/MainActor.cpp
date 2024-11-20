// Fill out your copyright notice in the Description page of Project Settings.


#include "MainActor.h"
#include "R1Actor.h"
// Sets default values
AMainActor::AMainActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainActor::BeginPlay()
{
	Super::BeginPlay();

	FVector Location(0, 0, 0);
	FRotator Rotation(0, 0, 0);
	AR1Actor* Actor = GetWorld()->SpawnActor<AR1Actor>(Location, Rotation);

}

// Called every frame
void AMainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

