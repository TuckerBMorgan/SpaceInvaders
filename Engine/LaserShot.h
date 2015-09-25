#pragma once

#include "Actor.h"

class LaserShot : public Actor
{
private:
	Actor* firedActor;

public:
	LaserShot();
	void OnCollision(Actor* otherActor);
	void Update();
};