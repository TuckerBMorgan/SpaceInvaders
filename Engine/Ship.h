#pragma once
#if _DX_
#include <d3d11.h>
#include <DirectXMath.h>
#endif

#include <unordered_map>
#include <string>
#include "Actor.h"
#include "GlobalStrucs.h"


using namespace DirectX;
using namespace std;

class Input;
class Component;
class TransformComponent;

class Ship : public Actor
{
public:
	Ship();
	~Ship();

public:
	virtual void Init(Input* input);

	virtual void Update();
	virtual void End();
	Vector3 GetPosition();
	virtual void OnCollision(Actor*);
protected:
	Input* inputPtr;
	float horizontalSpeed;
	float x, y, z;
	float health;

protected:
	TransformComponent* transform;

	
};