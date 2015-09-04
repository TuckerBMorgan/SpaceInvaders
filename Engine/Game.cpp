#include "Game.h"
#include "Actor.h"
#include "Ship.h"
#include "Input.h"
#include "RenderComponent.h"
#include "Graphics.h"
#include "Alien.h"
#include "TransformComponent.h"
#include "CollisionEngine.h"

Game::Game()
{
	allActors = vector<Actor*>();
}

#if _DX_
void Game::Start(Input* inpt)
{
	_input = inpt;

	CollisionEngine::Instance()->Start();

	//player ship
	Ship* ship = new Ship();
	ship->Start();
	ship->Init(_input);
	allActors.push_back(ship);


	for (int i = 0; i < 10; i++)
	{
		Alien* aln = new Alien();
		aln->Start();
		aln->Init(_input);
		static_cast<TransformComponent*>(aln->GetComponent(TransformComponent::ComponentName()))->SetPositionU(Vector3((i * 2.5f) - 10, 25, 0));
		allActors.push_back(aln);
	}
}
#endif
void Game::Update()
{
	
	CollisionEngine::Instance()->Update();
	for (int i = 0; i < allActors.size(); i++)
	{
		allActors[i]->Update();
	}
}

void Game::Render()
{
	vector<Actor*> renderActor;

	for (int i = 0; i < allActors.size(); i++)
	{
		if (allActors[i]->GetRenderer() != NULL)
		{
			if (allActors[i]->GetModel() != NULL)
			{
				renderActor.push_back(allActors[i]);
			}
		}
	}

	Graphics::Instance()->Render(renderActor);
}