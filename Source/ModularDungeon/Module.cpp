// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularDungeon.h"
#include "Module.h"


// Sets default values
AModule::AModule()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _root;

	_overlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	_overlapComp->OnComponentBeginOverlap.AddDynamic(this, &AModule::OnModuleBeginOverlap); // set up a notification for when this component overlaps something
	_overlapComp->SetupAttachment(_root);
	
	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_mesh->SetHiddenInGame(false);
	_mesh->SetupAttachment(_root);

	_isOverlappedByModule = false;
}

// Called when the game starts or when spawned
void AModule::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AModule::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AModule::OnModuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->GetName() != this->GetName() && OtherComp->GetName() == TEXT("OverlapBox"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("" + OtherComp->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Something overlapped me -> " + OtherActor->GetName()));
		_isOverlappedByModule = true;
	}
}
void AModule::OnModuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetName() != this->GetName() && OtherComp->GetName() == TEXT("OverlapBox"))
	{
		_isOverlappedByModule = false;
	}
}

void AModule::SetPivotOffset(const FVector& InPivotOffset)
{
	Super::AActor::SetPivotOffset(InPivotOffset);
}

