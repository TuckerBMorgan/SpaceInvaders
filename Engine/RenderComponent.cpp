#include "RenderComponent.h"
#include "ModelComponent.h"
#include "TransformComponent.h"
#include "Actor.h"

RenderComponent::RenderComponent(Actor* inActor, ModelComponent* model)
	:Component(inActor)
{
	this->model = model;
}


#if _DX_

void RenderComponent::Setup(ID3D11Device* device)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	vertexShaderBuffer = pixelShaderBuffer = 0;

	D3DCompileFromFile(L"../Engine/color.vs", NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&vertexShaderBuffer, &errorMessage);

	D3DCompileFromFile(L"../Engine/color.ps", NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&pixelShaderBuffer, &errorMessage);

	device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &_vertexShader);

	device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &_pixelShader);

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;


	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &_layout);

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	device->CreateBuffer(&matrixBufferDesc, NULL, &_matrixBuffer);

}
void RenderComponent::Render(ID3D11DeviceContext* deviceContext, int count, 
	XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix)
{
	
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;

	deviceContext->Map(_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	TransformComponent* transform = static_cast<TransformComponent*>(_actor->GetComponent(TransformComponent::ComponentName()));

	XMMATRIX combinedMatrix = worldMatrix;
	combinedMatrix = XMMatrixMultiply(combinedMatrix, viewMatrix);
	combinedMatrix = XMMatrixMultiply(combinedMatrix, projectionMatrix);
	combinedMatrix = XMMatrixTranspose(combinedMatrix);
		
	XMMATRIX modelMatrix =  DirectX::XMMatrixTranspose(transform->GetTranslationMatrix());
	modelMatrix = XMMatrixMultiply(modelMatrix, DirectX::XMMatrixTranspose(transform->GetRotationMatrixX()));
	modelMatrix = XMMatrixMultiply(modelMatrix, DirectX::XMMatrixTranspose(transform->GetScaleMatrix()));



	combinedMatrix = XMMatrixMultiply(combinedMatrix, modelMatrix);
	
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->combinedMatrix = combinedMatrix;

	deviceContext->Unmap(_matrixBuffer, 0);

	deviceContext->VSSetConstantBuffers(0, 1, &_matrixBuffer);

	deviceContext->IASetInputLayout(_layout);

	deviceContext->VSSetShader(_vertexShader, NULL, 0);
	deviceContext->PSSetShader(_pixelShader, NULL, 0);

	deviceContext->DrawIndexed(count, 0, 0);

}

#endif

void RenderComponent::Shutdown()
{

}

void RenderComponent::Cleanup()
{
	_vertexShader->Release();
	_pixelShader->Release();
	_layout->Release();
	_matrixBuffer->Release();
	
}