#pragma once


#include <windows.h>
#if _DX_
#include "D3D.h"
#endif
#include "Camera.h"
#include "Model.h"
#include "Ship.h"
#include <vector>
#include <unordered_map>

class Input;

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


class Actor;

class Graphics
{
public:
	Graphics();
	~Graphics();
	static Graphics* Instance(); 
	bool Init(int, int, HWND, Input* input);
	void Shutdown(); 
	void RegisterComponent(Actor*, TGUID);
	void DerigesterComponent(TGUID);
	bool Render();

	static Graphics* graphics;
private:
	Camera* m_camera;
	Model* m_model;
#if _DX_
	D3D* m_Direct3D;
public:
	ID3D11Device* GetD3DDevice();
#endif
	Ship* ship;
	vector<TGUID> updateRenders;
	unordered_map<int, Actor*> allRenderers;
};