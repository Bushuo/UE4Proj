// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Module.generated.h"

UCLASS()
class MODULARDUNGEON_API AModule : public AActor
{
	GENERATED_BODY()
public:
	// static mesh component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* _mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* _overlapComp;
	class USceneComponent* _root;
	bool _isOverlappedByModule;

	AModule();

	//called when something is overlapping the mesh component
	UFUNCTION()
	void OnModuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnModuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category="Util")
	void SetPivotOffset(const FVector& InPivotOffset);
};
