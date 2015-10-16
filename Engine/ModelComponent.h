#pragma once

#if _DX_
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;
#endif

#include "Component.h"


using namespace std;


class ModelComponent : public Component
{
protected:
	int indexCount;
	int vertexCount;
#if _DX_

	//Vertex Struct for the D3DX11 graphics version
	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

	//Vertex Varibles
	D3D11_BUFFER_DESC _vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA _vertexData;
	ID3D11Buffer* _vertexBuffer;

	//Index Varibles
	D3D11_BUFFER_DESC _indexBufferDesc;
	D3D11_SUBRESOURCE_DATA _indexData;
	ID3D11Buffer* _indexBuffer;

#endif

public:
	ModelComponent(Actor* inActor);
	static string ComponentName()
	{
		return "ModelComponent";
	};

	virtual void ShutdownBuffers();

	virtual void Cleanup() override;

	int GetIndexCount();

#if _DX_
	virtual void Setup(ID3D11Device*);
	void RenderBuffers(ID3D11DeviceContext* deviceContext);
	Vertex* vertices;
#endif
};