#include "System.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdShow)
{
	System* system;
	bool result;

	system = new System;
	if (!system)
	{
		return 0;
	}
	result = system->Init();
	if (result)
	{
		system->Run();
	}

	system->Shutdown();
	delete system;
	system = 0;

	return 0;

}