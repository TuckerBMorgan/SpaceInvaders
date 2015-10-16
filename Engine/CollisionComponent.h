#pragma once

#include "Component.h"

class TransformComponent;
struct Circle
{
	float radius;
};
struct Box
{
	//upper left = x1,y1
	//upper right = x2,y1
	//bottom right = x2, y2
	//bottom left = x1, y2
	float x1, x2;
	float y1, y2;

	bool isBoxColliding(Box* otherBox)
	{
		if (x1 > otherBox->x1 || otherBox->x2 > x2)
			return false;
		if (y1 > otherBox->y1 || otherBox->y2 > y2)
			return false;

		return true;
	}
	

};
struct Point
{
	float x;
	float y;
};

class CollisionComponent : public Component
{
public:
	CollisionComponent(Actor* inAct);
	static string ComponentName()
	{
		return "CollisionComponent";
	};
	Box GetBox();


	void Setup(TransformComponent*, Box box);
	virtual void Cleanup() override;

private:
	TransformComponent* transform;
	//CollisionType colType;
	Box bounds;
};