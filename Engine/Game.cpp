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
	removeIndexs = queue<int>();
	renderActor = vector<Actor*>();
}

#if _DX_
void Game::Start(Input* inpt)
{
	_input = inpt;

	CollisionEngine::Instance()->Start();

	//player ship
	Ship* ship = new Ship();
	ship->Start();
	ship->Init(_input, this);
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

	for (int i = 0; i < allActors.size(); i++)
	{
		if (allActors[i]->GetClean())
		{
			removeIndexs.emplace(i);
		}
	}

	int removeCount = 0;
	while (removeIndexs.size() > 0)
	{
		int index = removeIndexs.front() - removeCount;
		removeIndexs.pop();
		allActors[index]->Cleanup();
		Actor* act = allActors[index];
		allActors.erase(allActors.begin() + index);
		delete act;
		removeCount++;
		act = nullptr;
	}
	
}

void Game::Render()
{

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

	Graphics::Instance()->Render();
}

void Game::AddActor(Actor* act)
{
	allActors.push_back(act);
}