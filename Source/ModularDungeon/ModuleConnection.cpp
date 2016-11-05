// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularDungeon.h"
#include "ModuleConnection.h"


// Sets default values
AModuleConnection::AModuleConnection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//arrow->AttachToComponent(this->GetRootComponent(),);
	//sphere->

}

// Called when the game starts or when spawned
void AModuleConnection::BeginPlay()
{
	Super::BeginPlay();
	//const UWorld* world = GetWorld();
	//DrawDebugLine(world, GetActorTransform().GetLocation(), GetActorForwardVector(), FColor(255, 0, 0), true, -1.f, 0, 5.f);
	//FlushPersistentDebugLines(world);
}

// Called every frame
void AModuleConnection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

