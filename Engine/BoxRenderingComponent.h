#pragma once
#include "ModelComponent.h"


class BoxRenderingComponent : public ModelComponent
{
public:
	BoxRenderingComponent(Actor* inActor);
	static string ComponentName()
	{
		return "BoxRenderingComponent";
	};
#if _DX_
	void Setup(ID3D11Device* device);
#endif
};