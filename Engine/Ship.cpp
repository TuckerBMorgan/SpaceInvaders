
#include "Graphics.h"


#include "Ship.h"
#include "Input.h"
#include "Component.h"
#include "RenderComponent.h"
#include "ModelComponent.h"
#include "TransformComponent.h"
#include "ShapeComponent.h"
#include "CollisionComponent.h"
#include "CollisionEngine.h"


#include <Windows.h>


Ship::Ship()
	: Actor()
{
}
Ship::~Ship()
{
	
}

void Ship::Update()
{
	if (inputPtr->IsKeyDown(VK_RIGHT))
	{
		transform->SetPositionU(transform->GetPositionU() += Vector3(horizontalSpeed,0,0));
	}
	if (inputPtr->IsKeyDown(VK_LEFT))
	{
		transform->SetPositionU(transform->GetPositionU() -= Vector3(horizontalSpeed, 0, 0));
	}
}

void Ship::DoDamage(float DamageAmount)
{
	health -= DamageAmount;
	OnHealthChange(DamageAmount);

}

void Ship::OnHealthChange(float DamageAmount)
{

}

void Ship::Init(Input* input)
{
	inputPtr = input;

	horizontalSpeed = .1f;
	name = "MainShip";

	TransformComponent* trans = new TransformComponent(this);
	transform = trans;
	components.insert(std::pair<string, TransformComponent*>(TransformComponent::ComponentName(), trans));
	transform->SetPositionU(Vector3(0, -25, 0));
	transform->SetRoationU(Vector3(0, 0, 0));
	transform->SetScaleU(Vector3(1, 1, 1));

	ShapeComponent* boxrender = new ShapeComponent(this, ShapeComponent::ShapeType::Triangle);
	


#if _DX_
	boxrender
		->Setup(Graphics::Instance()->GetD3DDevice());
#endif

	components.insert(std::pair<string, ShapeComponent*>(ShapeComponent::ComponentName(), boxrender));

	model = boxrender;


	RenderComponent* render = new RenderComponent(this, boxrender);
#if _DX_
	render->Setup(Graphics::Instance()->GetD3DDevice());
#endif
	components.insert(std::pair<string, RenderComponent*>(RenderComponent::ComponentName(), render));
	renderer = render;


	Box box;
	box.x1 = 2;
	box.x2 = 0;
	box.y2 = 0;
	box.y1 = 2;

	CollisionComponent* col = new CollisionComponent(this);
	col->Setup(trans, box);
	CollisionEngine::Instance()->AddBody(col);
	components.insert(std::pair<string, CollisionComponent*>(CollisionComponent::ComponentName(), col));

}

void Ship::End()
{

}

Vector3 Ship::GetPosition()
{	
	return transform->GetPositionU();
}

void Ship::OnCollision(Actor* otherActor)
{
	if (otherActor->GetTag() == "Alien")
	{
		health -= 10;
	}
}