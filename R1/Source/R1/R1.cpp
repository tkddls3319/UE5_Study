// Copyright Epic Games, Inc. All Rights Reserved.

#include "R1.h"
#include "Modules/ModuleManager.h"


class FR1Module : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
	}

	virtual void ShutdownModule() override
	{
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, R1, "R1" );
