#include "Alien.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "ShapeComponent.h"
#include "Graphics.h"
#include "CollisionEngine.h"
#include "CollisionComponent.h"
#include "Tags.h"
#include "Guid.h"

Alien::Alien()
{
}
void Alien::Init(Input* intp)
{
	TransformComponent* trans = new TransformComponent(this);
	transform = trans;
	components.insert(std::pair<string, TransformComponent*>(TransformComponent::ComponentName(), trans));
	transform->SetPositionU(Vector3(0, 25, 0));
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
	box.y1 = 0;
	box.y2 = 2;
	col->Setup(trans, box);
	components.insert(std::pair<string, CollisionComponent*>(CollisionComponent::ComponentName(), col));

	CollisionEngine::Instance()->AddBody(col);

	tag = ALIEN;
}

void Alien::Update()
{
	transform->SetPositionU(transform->GetPositionU() += Vector3(0,-0.1f,0));
}