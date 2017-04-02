// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularDungeon.h"
#include "Kismet/KismetMathLibrary.h"
#include "DungeonController.h"

int TEST_INT = 0;

// Sets default values
ADungeonController::ADungeonController()
{
 	// Set this actor to call Tick() every frame.
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
		int attempts = 0;
		//spawn starting module
		AActor* startModule = GetWorld()->SpawnActor<AModule>(_startModule, FVector(0.f, 0.f, 0.f), FRotator(0.f, 45.f, 0.f), spawnParams);

		//get components from startmodule and paste in array
		TArray<UChildActorComponent*> pendingExits;
		startModule->GetComponents(pendingExits);

		//the dungeon algorithm
		for (int32 x = 0; x < _iterrations; x++)
		{
			TArray<UChildActorComponent*> newExits;
			for (int i = 0; i < pendingExits.Num(); i++)
			{

				//get random tag from i-th component
				FName tag = pendingExits[i]->ComponentTags[FMath::RandRange(0, pendingExits[i]->ComponentTags.Num() - 1)];
				//spawn new module at dummy location
				FVector dummyLocation;
				dummyLocation.Set(-100000, -100000, -100000);
				//init to prevent error
				AModule* nextModule = GetWorld()->SpawnActor<AModule>(_test, dummyLocation, FRotator::ZeroRotator, spawnParams);
				nextModule->Destroy();

				//TODO
				// *try to place without collision to other modules
				// *if fail try again
				// *if success proceed
				// *if fails try with different module for *specified times* 
				//		or end here and mark as not connected

				// *chose random module
				//spawn module matching the random tag
				
				while (attempts <= _attemptsForSpawning)
				{
					if (tag == "corr")
					{
						int num = FMath::RandRange(0, _corrs.Num() - 1);
						nextModule = GetWorld()->SpawnActor<AModule>(_corrs[num], dummyLocation, FRotator::ZeroRotator, spawnParams);
					}
					else if (tag == "junc")
					{
						int num = FMath::RandRange(0, _juncs.Num() - 1);
						nextModule = GetWorld()->SpawnActor<AModule>(_juncs[num], dummyLocation, FRotator::ZeroRotator, spawnParams);
					}
					else if (tag == "room")
					{
						int num = FMath::RandRange(0, _rooms.Num() - 1);
						nextModule = GetWorld()->SpawnActor<AModule>(_rooms[num], dummyLocation, FRotator::ZeroRotator, spawnParams);
					}

					//get new module exits
					TArray<UChildActorComponent*> newModuleExits;
					nextModule->GetComponents(newModuleExits);
					//choose random exit
					AActor* exitToMatch = newModuleExits[FMath::RandRange(0, newModuleExits.Num() - 1)]->GetChildActor();
					//match exits
					MatchExits(pendingExits[i]->GetChildActor(), exitToMatch);
					if (nextModule->_isOverlappedByModule)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("deleted overlapping module"));
						nextModule->Destroy();
						attempts++;
					}
					else
					{
						//get remaining unconnected exits from new module
						for (int e = 0; e < newModuleExits.Num(); e++)
						{
							if (newModuleExits[e]->GetChildActor() != exitToMatch)
								newExits.Add(newModuleExits[e]);
						}
						attempts++;
						break;
					}
				}

				//add placed verified module to array
				_dungeonModules.Add(nextModule);
				nextModule = NULL;
			}
			//update pending exits
			pendingExits = newExits;
		}
		//TODO
		//* mark all unconnected exits and place *defined object*
	}
}

void ADungeonController::MatchExits(AActor* exit1, AActor* exit2)
{
	AActor* movingModule = exit2->GetParentActor();
	FVector forwardVectorToMatch = -exit1->GetActorForwardVector();
	float correctiveRotation = Azimuth(forwardVectorToMatch) - Azimuth(exit2->GetActorForwardVector());

	movingModule->SetPivotOffset(exit1->GetActorLocation());
	movingModule->SetActorRotation(FRotator(0.f, correctiveRotation, 0.f), ETeleportType::TeleportPhysics);
	movingModule->SetPivotOffset(FVector::ZeroVector);

	FVector acLoc = movingModule->GetActorLocation();
	FVector correctiveTranslation = exit1->GetActorLocation() - exit2->GetActorLocation();
	movingModule->SetActorLocation(acLoc + correctiveTranslation);
	movingModule = NULL;
}

float ADungeonController::Azimuth(FVector vec)
{
	return AngleBetween(FVector::ForwardVector, vec) * FMath::Sign<float>(vec.Y);
}

float ADungeonController::AngleBetween(FVector from, FVector to)
{
	from.Normalize();
	to.Normalize();
	return UKismetMathLibrary::DegAcos(FVector::DotProduct(from, to));
}