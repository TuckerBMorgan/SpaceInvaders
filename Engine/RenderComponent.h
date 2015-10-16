#pragma once

#if _DX_

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>

using namespace DirectX;

#endif


#include "Component.h"


using namespace std;
class ModelComponent;

class RenderComponent : public Component
{
protected:
	
	ModelComponent* model;

public:
	RenderComponent(Actor* inActor, ModelComponent* inModel);
	static string ComponentName()
	{
		return " RenderComponent";
	};

	#if _DX_

	struct MatrixBufferType
	{
		XMMATRIX combinedMatrix;
	};

public:

	void Setup(ID3D11Device*);
	void Render(ID3D11DeviceContext*, int, 
		XMMATRIX&, XMMATRIX&, XMMATRIX&);
	virtual void Cleanup() override;

private:

	ID3D11VertexShader* _vertexShader;
	ID3D11PixelShader* _pixelShader;
	ID3D11InputLayout* _layout;
	ID3D11Buffer* _matrixBuffer;
	
	#endif
	void Shutdown();
};