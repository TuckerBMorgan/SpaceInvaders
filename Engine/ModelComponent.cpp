#include "ModelComponent.h"

ModelComponent::ModelComponent(Actor* inActor)
	:Component(inActor)
{

}

void ModelComponent::ShutdownBuffers()
{
#if _DX_
	if (_indexBuffer)
	{
		_indexBuffer->Release();
		_indexBuffer = 0;
	}
	if (_vertexBuffer)
	{
		_vertexBuffer->Release();
		_vertexBuffer = 0;
	}

#endif
}

#if _DX_
void ModelComponent::Setup(ID3D11Device* device)
{

}
void ModelComponent::RenderBuffers(ID3D11DeviceContext* deviceContext)
{

	unsigned int stride;
	unsigned int offset;

	stride = sizeof(Vertex);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);

	deviceContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
};
int ModelComponent::GetIndexCount()
{
	return indexCount;
}



#endif


void ModelComponent::Cleanup()
{

#if _DX_
	ShutdownBuffers();
#endif

	
	delete[] vertices;

}