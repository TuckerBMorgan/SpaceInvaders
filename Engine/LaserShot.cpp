#include "LaserShot.h"
#include "Ship.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "ShapeComponent.h"
#include "Graphics.h"
#include "CollisionEngine.h"
#include "CollisionComponent.h"
#include "Tags.h"
#include "Guid.h"

LaserShot::LaserShot()
	:Actor()
{

}

void LaserShot::Init(Actor* act)
{
	firedActor = act;

	TransformComponent* trans = new TransformComponent(this);
	transform = trans;
	components.insert(std::pair<string, TransformComponent*>(TransformComponent::ComponentName(), trans));

	TransformComponent* actTra = static_cast<TransformComponent*>(act->GetComponent(TransformComponent::ComponentName()));

	transform->SetPositionU(Vector3(0, actTra->GetPositionU().y + 10, 0));
	transform->SetRoationU(Vector3(0, 0, 0));
	transform->SetScaleU(Vector3(1, 1, 1));

	ShapeComponent* shape = new ShapeComponent(this, ShapeComponent::ShapeComponent::Box);

#if _DX_
	shape->Setup(Graphics::Instance()->GetD3DDevice());
#endif

	components.insert(std::pair<string, ShapeComponent*>(ShapeComponent::ComponentName(), shape));

	model = shape;

	RenderComponent* render = new RenderComponent(this, shape);

#if _DX_
	render->Setup(Graphics::Instance()->GetD3DDevice());
#endif


	components.insert(std::pair<string, RenderComponent*>(RenderComponent::ComponentName(), render));
	renderer = render;
	Graphics::Instance()->RegisterComponent(this, *guid);

	CollisionComponent* col = new CollisionComponent(this);
	Box box;
	box.x1 = 2;
	box.x2 = 0;
	box.y1 = 2;
	box.y2 = 0;
	col->Setup(trans, box);
	components.insert(std::pair<string, CollisionComponent*>(CollisionComponent::ComponentName(), col));

	CollisionEngine::Instance()->AddBody(col);
}

void LaserShot::Update()
{
	transform->SetPositionU(transform->GetPositionU() += Vector3(0, 1, 0));
}

void LaserShot::OnCollision(Actor* actor)
{
	if (actor != firedActor)
	{
		if (actor->GetTag() == "Alien" || actor->GetTag() == "Ship")
		{
			static_cast<Ship*>(actor)->DoDamage(10);

			toClean = true;
		}
	}
}

void LaserShot::Cleanup()
{
	CollisionEngine::Instance()->RemoveBody((CollisionComponent*)components[CollisionComponent::ComponentName()]);
	Graphics::Instance()->DerigesterComponent(*guid);
	
	ComponentCleanup();

}