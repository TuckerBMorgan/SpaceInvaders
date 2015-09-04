#pragma once
#include "Component.h"

#if _DX_
#include <d3d11.h>
#include <directxmath.h>
#include "GlobalStrucs.h"
using namespace DirectX;
#endif

class TransformComponent : public Component
{
public:
	TransformComponent(Actor* inActor);

	static std::string ComponentName()
	{
		return "TransformComponent";
	}

#if _DX_

	//Translation Getters
	XMMATRIX GetTranslationMatrix();
	XMFLOAT3 GetPosition();

	//Rotaiton Getters
	XMMATRIX GetRotationMatrixX();
	XMFLOAT3 GetRotation();

	//Scale Getters
	XMMATRIX GetScaleMatrix();
	XMFLOAT3 GetScale();

#endif
	
	//Universal Position Accsessor 
	Vector3 GetPositionU()
	{
		return Vector3(_posX, _posY, _posZ);
	};

	void SetPositionU(Vector3 inPos)
	{
		_posX = inPos.x;
		_posY = inPos.y;
		_posZ = inPos.z;
	};

	//Universal rotation accessor
	Vector3 GetRoationU()
	{
		return Vector3(_rotX, _rotY, _rotZ);
	};
	
	void SetRoationU(Vector3 inRot)
	{
		_rotX = inRot.x;
		_rotY = inRot.y;
		_rotZ = inRot.z;
	}

	//Universal scale accessor
	Vector3 GetScaleU()
	{
		return Vector3(_scaX, _scaY, _scaZ);
	}

	void SetScaleU(Vector3 inSca)
	{
		_scaX = inSca.x;
		_scaY = inSca.y;
		_scaZ = inSca.z;
	}


private:
	//Position of object
	float _posX, _posY, _posZ;
	//Rotation of object
	float _rotX, _rotY, _rotZ;
	//Scale of object
	float _scaX, _scaY, _scaZ;
};