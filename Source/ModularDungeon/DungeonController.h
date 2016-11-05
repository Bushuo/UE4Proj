// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Module.h"
#include "DungeonController.generated.h"

UCLASS()
class MODULARDUNGEON_API ADungeonController : public AActor
{
	GENERATED_BODY()

public:
	ADungeonController();

	virtual void BeginPlay() override;

	static float AngleBetween(FVector from, FVector to);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
		int32 m_iterrations;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	//TArray<TSubclassOf<AModule>> m_modules;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
		TSubclassOf<AModule> m_startModule;
	UPROPERTY(BlueprintReadOnly)
		TArray<AActor*> m_dungeonModules;
private:
	

	void MatchExits(AActor* oldE, AActor* newE);
	static float Azimuth(FVector vec);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Room")
		TSubclassOf<AModule> m_test;
	UPROPERTY(EditDefaultsOnly, Category = "Room")
		TArray<TSubclassOf<AModule>> m_rooms;
	UPROPERTY(EditDefaultsOnly, Category = "Junction")
		TArray<TSubclassOf<AModule>> m_juncs;
	UPROPERTY(EditDefaultsOnly, Category = "Corridor")
		TArray<TSubclassOf<AModule>> m_corrs;
};
