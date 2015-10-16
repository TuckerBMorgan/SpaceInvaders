#include "Actor.h"
#include "RenderComponent.h"
#include "ModelComponent.h"
#include "Guid.h"




Actor::Actor()
{
	components = unordered_map<string, Component*>();
	guid = TGUID::CreateGUID();
	toClean = false;
}

void Actor::Start()
{
	
}

void Actor::Update()
{

}
string Actor::GetName()
{
	return name;
}

Component* Actor::GetComponent(string componentName)
{
	if (components.count(componentName) > 0)
	{
		return components[componentName];
	}
	else
	{
		return NULL;
	}
}

RenderComponent* Actor::GetRenderer()
{
	if (renderer != NULL)
	{
		return renderer;
	}
	return NULL;
}

ModelComponent* Actor::GetModel()
{
	if (model != NULL)
	{
		return model;
	}
	return NULL;
}

void Actor::OnCollision(Actor *)
{

}
#include <queue>
void Actor::ComponentCleanup()
{
	queue<Component*> comps;
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		if (it->second != nullptr)
		{
			it->second->Cleanup();
			comps.push(it->second);
		}	
	}
 	components.clear();
}
