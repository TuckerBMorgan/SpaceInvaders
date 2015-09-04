#pragma once


#include "ModelComponent.h"

class ShapeComponent : public ModelComponent
{
public:
	enum ShapeType
	{
		Box,
		Triangle
	};


	ShapeComponent(Actor*);
	ShapeComponent(Actor*, ShapeType);

	static string ComponentName()
	{
		return "ShapeComponent";
	}

#if _DX_
	void Setup(ID3D11Device*);
#endif
private:
	ShapeType shapeType;
};
