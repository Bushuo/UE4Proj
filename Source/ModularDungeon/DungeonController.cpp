// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularDungeon.h"
#include "Kismet/KismetMathLibrary.h"
#include "DungeonController.h"


// Sets default values
ADungeonController::ADungeonController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADungeonController::BeginPlay()
{
	Super::BeginPlay();

	const UWorld* world = GetWorld();
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Instigator;

	if (world)
	{
		//spawn starting module
		AActor* startModule = GetWorld()->SpawnActor<AModule>(m_startModule, FVector(0.f, 0.f, 0.f), FRotator(0.f, 45.f, 0.f), spawnParams);

		TArray<UChildActorComponent*> pendingExits;
		startModule->GetComponents(pendingExits);
		//driver
		for (int32 x = 0; x < m_iterrations; x++)
		{
			TArray<UChildActorComponent*> newExits;
			for (int i = 0; i < pendingExits.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("pending Exits num = %i"), pendingExits.Num());
				//get random tag from i-th component
				FName tag = pendingExits[i]->ComponentTags[FMath::RandRange(0, pendingExits[i]->ComponentTags.Num() - 1)];
				UE_LOG(LogTemp, Warning, TEXT("random tag = %s"),*tag.ToString());
				//spawn new module at dummy location
				FVector dummyLocation;
				dummyLocation.Set(-1000, -1000, 0);
				//init to prevent error
				AActor* newModule = GetWorld()->SpawnActor<AModule>(m_test, dummyLocation, FRotator::ZeroRotator, spawnParams);
				newModule->Destroy();
				//spawn correct matching module at dummy loc
				if (tag == "corr")
				{
					int32 num = FMath::RandRange(0, m_corrs.Num()-1);
					newModule = GetWorld()->SpawnActor<AModule>(m_corrs[num], dummyLocation, FRotator::ZeroRotator, spawnParams);
					m_dungeonModules.Add(newModule);
				}
				else if (tag == "junc")
				{
					int32 num = FMath::RandRange(0, m_juncs.Num()-1);
					newModule = GetWorld()->SpawnActor<AModule>(m_juncs[num], dummyLocation, FRotator::ZeroRotator, spawnParams);
					m_dungeonModules.Add(newModule);
				}
				else if (tag == "room")
				{
					int32 num = FMath::RandRange(0, m_rooms.Num()-1);
					newModule = GetWorld()->SpawnActor<AModule>(m_rooms[num], dummyLocation, FRotator::ZeroRotator, spawnParams);
					m_dungeonModules.Add(newModule);
				}
				//get new module exits
				TArray<UChildActorComponent*> newModuleExits;
				newModule->GetComponents(newModuleExits);
				//choose random exit
				AActor* exitToMatch = newModuleExits[FMath::RandRange(0, newModuleExits.Num()-1)]->GetChildActor();
				//match exits
				MatchExits(pendingExits[i]->GetChildActor(), exitToMatch);
				//get remaining unconnected exits from new module
				for (int e = 0; e < newModuleExits.Num(); e++)
				{
					if (newModuleExits[e]->GetChildActor() != exitToMatch)
						newExits.Add(newModuleExits[e]);
				}
			}
			pendingExits = newExits;
		}
	}
}

void ADungeonController::MatchExits(AActor* oldE, AActor* newE)
{
	UE_LOG(LogTemp, Warning, TEXT("in MatchExits"));
	AActor* newModule = newE->GetParentActor();
	FVector forwardVectorToMatch = -oldE->GetActorForwardVector();
	float correctiveRotation = Azimuth(forwardVectorToMatch) - Azimuth(newE->GetActorForwardVector());

	newModule->SetPivotOffset(oldE->GetActorLocation());
	newModule->SetActorRotation(FRotator(0.f, correctiveRotation, 0.f), ETeleportType::TeleportPhysics);
	newModule->SetPivotOffset(FVector::ZeroVector);

	FVector acLoc = newModule->GetActorLocation();
	FVector correctiveTranslation = oldE->GetActorLocation() - newE->GetActorLocation();
	newModule->SetActorLocation(acLoc + correctiveTranslation);
}

float ADungeonController::Azimuth(FVector vec)
{
	UE_LOG(LogTemp, Warning, TEXT("vecY = %.10f"), vec.Y);
	float angle = AngleBetween(FVector::ForwardVector, vec) * FMath::Sign<float>(vec.Y);
	return angle;
}

float ADungeonController::AngleBetween(FVector from, FVector to)
{
	from.Normalize();
	to.Normalize();
	float angle = UKismetMathLibrary::DegAcos(FVector::DotProduct(from, to));
	return angle;
}