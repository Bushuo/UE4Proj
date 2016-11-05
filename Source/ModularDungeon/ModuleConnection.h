// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Components/ArrowComponent.h"
#include "ModuleConnection.generated.h"

UCLASS()
class MODULARDUNGEON_API AModuleConnection : public AActor
{
	GENERATED_BODY()

public:
	bool m_isDefault;

	// Sets default values for this actor's properties
	AModuleConnection();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
};
