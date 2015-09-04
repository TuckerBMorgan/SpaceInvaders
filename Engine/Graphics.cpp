#include "Graphics.h"
#include "Input.h"
#include "Actor.h"
#include "ModelComponent.h"
#include "RenderComponent.h"

Graphics* Graphics::graphics = NULL;


Graphics::Graphics()
{
	m_Direct3D = 0;
	m_camera = 0;
	m_model = 0;
	ship = 0;
}

Graphics::~Graphics()
{
}


bool Graphics::Init(int screenWidth, int screenHeight, HWND hwnd, Input* input)
{

	graphics = this;
	bool result;

#if _DX_

	m_Direct3D = new D3D;
	if (!m_Direct3D)
	{
		return false;
	}
	
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

#endif
	m_camera = new Camera;
	if (!m_camera)
	{
		return false;
	}
	m_camera->SetPosition(0.0f, 0.0f, -10.0f);


	m_model = new Model;
	if (!m_model)
	{
		return false;
	}

	result = m_model->Init(m_Direct3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not init the model object", L"Error", MB_OK);
		return false;
	}
	return true;
}
#if _DX_
ID3D11Device* Graphics::GetD3DDevice()
{
	return m_Direct3D->GetDevice();
}

#endif

void Graphics::Shutdown()
{

	if (m_model)
	{
		m_model->Shutdown();
		delete m_model;
		m_model = 0;
	}

	if (m_camera)
	{
		delete m_camera;
		m_camera = 0;
	}

	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
	return;
}


Graphics* Graphics::Instance()
{
	if (!graphics)
	{
		graphics = new Graphics();
	}
	return graphics;
}

bool Graphics::Render(vector<Actor*> renders)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_camera->Render();

	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetOrthoMatrix(projectionMatrix);


	for (int i = 0; i < renders.size(); i++)
	{
		renders[i]->GetModel()->RenderBuffers(m_Direct3D->GetDeviceContext());
		renders[i]->GetRenderer()->Render(m_Direct3D->GetDeviceContext(), renders[i]->GetModel()->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	}

	m_Direct3D->EndScene();
	return true;
}
