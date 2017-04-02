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
	int32 _iterrations;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	int32 _attemptsForSpawning;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<AModule> _startModule;
	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> _dungeonModules;
private:
	void MatchExits(AActor* exit1, AActor* exit2);
	static float Azimuth(FVector vec);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<AModule> _test;
	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TArray<TSubclassOf<AModule>> _rooms;
	UPROPERTY(EditDefaultsOnly, Category = "Junction")
	TArray<TSubclassOf<AModule>> _juncs;
	UPROPERTY(EditDefaultsOnly, Category = "Corridor")
	TArray<TSubclassOf<AModule>> _corrs;
};
