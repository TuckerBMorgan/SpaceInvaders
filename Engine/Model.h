#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Model
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};
	
public:
	Model();
	~Model();

	bool Init(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();



private:
	bool InitBuffers(ID3D11Device*);
	void ShutdownBuffer();
	void RenderBuffers(ID3D11DeviceContext*);

	ID3D11Device* _device;

	VertexType* vertices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
public:
	XMMATRIX GetPosition();
private:
	XMFLOAT3 pos;
	int m_vertexCount, m_indexCount;
public:
	void SetPosition(XMFLOAT3 pos);
};