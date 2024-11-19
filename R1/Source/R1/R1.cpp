// Copyright Epic Games, Inc. All Rights Reserved.

#include "R1.h"
#include "Modules/ModuleManager.h"
#include "R1LogChannels.h"
class FR1Module : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		//시작
		UE_LOG(LogR1, Log, TEXT("StartupModule 시작"));
	}

	virtual void ShutdownModule() override
	{
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FR1Module, R1, "R1" );
