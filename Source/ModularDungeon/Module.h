// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ModuleConnection.h"
#include "Module.generated.h"

UCLASS()
class MODULARDUNGEON_API AModule : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_roomMesh;

	AModule();

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;
};
