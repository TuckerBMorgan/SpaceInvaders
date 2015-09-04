#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "Graphics.h"
#include "Input.h"

class Game;

class System
{
public:
	System();
	~System();

	bool Init();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	Input *m_Input;
	Graphics* m_Graphics;
	Game* m_game;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static System* ApplicationHandle = 0;
