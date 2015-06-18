#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Director.h"
#include "Scene.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	AllocConsole();

	if (!theGame->Init(false, 800, 600))
	{
		Error("ϵͳ��ʼ��ʧ�ܣ�");
		return 1;
	}

	auto scene = Create<Scene>();
	theDirector->RunWithScene(scene);

	theGame->Run();
	theGame->Cleanup();

	FreeConsole();

	return 0;

}
