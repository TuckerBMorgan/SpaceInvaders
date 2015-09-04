#pragma once
#include <vector>

using namespace std;

class CollisionComponent;

class CollisionEngine
{
	CollisionEngine();
public:
	void AddBody(CollisionComponent*);
	void Update();
	void Start()
	{

	}
	static CollisionEngine* Instance();
private:
	vector<CollisionComponent*> bodies;
	static CollisionEngine* _instance;
};