#include "CollisionComponent.h"
#include "TransformComponent.h"

CollisionComponent::CollisionComponent(Actor * inAct)
	:Component(inAct)
{

}
void CollisionComponent::Setup(TransformComponent* trans, Box box)
{
	transform = trans;
	bounds = box;
}

Box CollisionComponent::GetBox()
{
	Box useBox;
	useBox.x1 = bounds.x1 - transform->GetPositionU().x;
	useBox.x2 = bounds.x2 - transform->GetPositionU().x;
	useBox.y1 = bounds.y1 - transform->GetPositionU().y;
	useBox.y2 = bounds.y2 - transform->GetPositionU().y;
	return useBox;
}