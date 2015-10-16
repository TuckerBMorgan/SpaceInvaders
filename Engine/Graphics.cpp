#include "Graphics.h"
#include "Input.h"
#include "Actor.h"
#include "ModelComponent.h"
#include "RenderComponent.h"
#include "Guid.h"

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

void Graphics::RegisterComponent(Actor* renderComp, TGUID guid)
{
	updateRenders.push_back(guid);
	allRenderers.insert(std::pair<int, Actor*>(guid.number, renderComp));
}

void Graphics::DerigesterComponent(TGUID guid)
{
	int position = -1;
	for (int i = 0; i < updateRenders.size(); i++)
	{
		if (guid == updateRenders[i])
		{
			position = i;
		}
	}
	if (position >= 0)
	{
		updateRenders.erase(updateRenders.begin() + position);
	}
	

	allRenderers.erase(guid.number);
}

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

ID3D11VertexShader* Graphics::GetVertexShader(string name)
{

	return nullptr;
}

ID3D11PixelShader* Graphics::GetPixelShader(string name)
{

	return nullptr;
}

bool Graphics::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_camera->Render();

	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetOrthoMatrix(projectionMatrix);

	for (int i = 0; i < updateRenders.size(); i++)
	{
		Actor* updateRender = allRenderers[updateRenders[i].number];
		if (updateRender != NULL)
		{
			updateRender->GetModel()->RenderBuffers(m_Direct3D->GetDeviceContext());
			updateRender->GetRenderer()->Render(m_Direct3D->GetDeviceContext(), updateRender->GetModel()->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
		}
	}
	

	m_Direct3D->EndScene();
	return true;
}
