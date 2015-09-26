#pragma once

#include "Actor.h"

class TransformComponent;

class LaserShot : public Actor
{
private:
	Actor* firedActor;
	TransformComponent* transform;

public:
	LaserShot();
	void OnCollision(Actor* otherActor);
	virtual void Update();
	void Init(Actor*);
};