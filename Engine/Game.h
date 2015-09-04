#pragma once
#include <vector>

#if _DX_
#include <d3d11.h>
#endif

using namespace std;

class Actor;
class Input;

class Game
{
	Input* _input;
	vector<Actor*> allActors;

#if _DX_

#endif

public:
	Game();
	void Start(Input* input);

	void Update();

	void Render();
};