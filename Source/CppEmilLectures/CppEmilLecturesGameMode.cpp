// Copyright Epic Games, Inc. All Rights Reserved.

#include "CppEmilLecturesGameMode.h"
#include "CppEmilLecturesCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACppEmilLecturesGameMode::ACppEmilLecturesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
