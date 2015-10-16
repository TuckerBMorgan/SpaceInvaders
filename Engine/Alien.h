#pragma once
#include "Ship.h"
class Input;

class Alien : public Ship
{
public:
	Alien();
	void Update();
	void Init(Input* in);
	
private: 
	float health;


};