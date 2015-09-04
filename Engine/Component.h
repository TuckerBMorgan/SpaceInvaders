#pragma once
#include <string>

using namespace std;

class Actor;

class Component
{
protected:
	Actor* _actor;

public:
	Component(Actor* inActor)
	{
		_actor = inActor;
	};
	static string ComponentName()
	{
		return "Component";
	};
	Actor* GetActor()
	{
		return _actor;
	}
};