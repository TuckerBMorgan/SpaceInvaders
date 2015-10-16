#include "ShapeComponent.h"

ShapeComponent::ShapeComponent(Actor * inActor)
	:ModelComponent(inActor)
{

}
ShapeComponent::ShapeComponent(Actor* inActor, ShapeType type)
	:ModelComponent(inActor)
{
	shapeType = type;
}

void ShapeComponent::Setup(ID3D11Device* device)
{


	unsigned long* indices;
	HRESULT result;

	switch (shapeType)
	{
	case ShapeType::Box:
		vertices = new Vertex[4];
		vertexCount = 4;

		indices = new unsigned long[6];

		vertices[0].position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertices[0].color = XMFLOAT4(1.0f  , 0.5f, 0.3f, 1.0f);

		vertices[1].position = XMFLOAT3(0.0f, 2.0f, 0.0f);
		vertices[1].color = XMFLOAT4(0.4, 0.5f, 0.3f, 1.0f);

		vertices[2].position = XMFLOAT3(2.0f, 2.0f, 0.0f);
		vertices[2].color = XMFLOAT4(0.4, 0.5f, 0.3f, 1.0f);

		vertices[3].position = XMFLOAT3(2.0f, 0.0f, 0.0f);
		vertices[3].color = XMFLOAT4(0.4, 0.5f, 0.3f, 1.0f);

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;

		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;

		indexCount = 6;


		_vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		_vertexBufferDesc.ByteWidth = sizeof(Vertex) * 4;
		_vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		_vertexBufferDesc.CPUAccessFlags = 0;
		_vertexBufferDesc.MiscFlags = 0;
		_vertexBufferDesc.StructureByteStride = 0;

		_vertexData.pSysMem = vertices;
		_vertexData.SysMemPitch = 0;
		_vertexData.SysMemSlicePitch = 0;

		_indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		_indexBufferDesc.ByteWidth = sizeof(unsigned long) * 6;
		_indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		_indexBufferDesc.CPUAccessFlags = 0;
		_indexBufferDesc.MiscFlags = 0;
		_indexBufferDesc.StructureByteStride = 0;

		_indexData.pSysMem = indices;
		_indexData.SysMemPitch = 0;
		_indexData.SysMemSlicePitch = 0;

		break;

	case ShapeType::Triangle:
		vertexCount = 3;
		vertices = new Vertex[3];

		indices = new unsigned long[3];

		vertices[0].position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertices[0].color = XMFLOAT4(0.0, 2.0f, 0.0, 1.0f);

		vertices[1].position = XMFLOAT3(1.0f, 2.0f, 0.0f);
		vertices[1].color = XMFLOAT4(0.0, 2.0f, 0.0, 1.0f);

		vertices[2].position = XMFLOAT3(2.0f, 0.0f, 0.0f);
		vertices[2].color = XMFLOAT4(0.0, 1.0f, 0.0, 1.0f);

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;

		indexCount = 3;

		_vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		_vertexBufferDesc.ByteWidth = sizeof(Vertex) * 3;
		_vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		_vertexBufferDesc.CPUAccessFlags = 0;
		_vertexBufferDesc.MiscFlags = 0;
		_vertexBufferDesc.StructureByteStride = 0;

		_vertexData.pSysMem = vertices;
		_vertexData.SysMemPitch = 0;
		_vertexData.SysMemSlicePitch = 0;

		_indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		_indexBufferDesc.ByteWidth = sizeof(unsigned long) * 3;
		_indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		_indexBufferDesc.CPUAccessFlags = 0;
		_indexBufferDesc.MiscFlags = 0;
		_indexBufferDesc.StructureByteStride = 0;

		_indexData.pSysMem = indices;
		_indexData.SysMemPitch = 0;
		_indexData.SysMemSlicePitch = 0;

		break;

	default:
		break;
	}

	device->CreateBuffer(&_vertexBufferDesc, &_vertexData, &_vertexBuffer);
	device->CreateBuffer(&_indexBufferDesc, &_indexData, &_indexBuffer);
}
