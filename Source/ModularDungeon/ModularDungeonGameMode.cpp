// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ModularDungeon.h"
#include "ModularDungeonGameMode.h"
#include "ModularDungeonHUD.h"
#include "ModularDungeonCharacter.h"

AModularDungeonGameMode::AModularDungeonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AModularDungeonHUD::StaticClass();
}
