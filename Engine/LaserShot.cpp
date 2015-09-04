#include "LaserShot.h"
#include "Ship.h"

LaserShot::LaserShot()
{
}

void LaserShot::OnCollision(Actor* actor)
{
	if (actor != firedActor)
	{
		if (actor->GetTag() == "Alien" || actor->GetTag() == "Ship")
		{
			static_cast<Ship*>(actor)->DoDamage(10);
		}
	}
}