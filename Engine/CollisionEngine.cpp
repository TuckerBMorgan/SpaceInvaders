#include "CollisionEngine.h"
#include "CollisionComponent.h"
#include "Actor.h"
#include "TransformComponent.h"

CollisionEngine* CollisionEngine::_instance = 0;

CollisionEngine::CollisionEngine()
{

}

void CollisionEngine::AddBody(CollisionComponent* colcomp)
{
	bodies.push_back(colcomp);
}

CollisionEngine* CollisionEngine::Instance()
{
	if (_instance == NULL)
	{
		_instance = new CollisionEngine();
	}
	return _instance;
}

void CollisionEngine::Update()
{
	for (int i = 0; i < bodies.size(); i++)
	{
		CollisionComponent* thisBody = bodies[i];
		for (int bods = 0; bods < bodies.size(); bods++)
		{
			if (bodies[bods] != thisBody)
			{
				if (bodies[bods]->GetBox().isBoxColliding(&thisBody->GetBox()))
				{
					thisBody->GetActor()->OnCollision(bodies[bods]->GetActor());
				}
			}
		}
	}
}

