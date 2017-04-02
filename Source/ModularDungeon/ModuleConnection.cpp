// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularDungeon.h"
#include "ModuleConnection.h"


// Sets default values
AModuleConnection::AModuleConnection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AModuleConnection::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AModuleConnection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

