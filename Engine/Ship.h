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
class Game;
class LaserShot;

class Ship : public Actor
{
public:
	Ship();
	~Ship();

public:
	virtual void Init(Input* input, Game*);
	virtual void DoDamage(float damageAmout);
	virtual void Update() override;
	virtual void End();
	Vector3 GetPosition();
	virtual void OnCollision(Actor*) override;
	virtual void Cleanup() override;

protected:
	Input* inputPtr;
	float horizontalSpeed;
	float x, y, z;
	float health;
	virtual void OnHealthChange(float amount);
	Game* game;
	bool test;
protected:
	TransformComponent* transform;
	vector<LaserShot*> shots;
	
};