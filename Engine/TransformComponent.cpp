#include "TransformComponent.h"

TransformComponent::TransformComponent(Actor* inActor)
	: Component(inActor)
{

}

#if _DX_
XMFLOAT3 TransformComponent::GetPosition()
{
	return XMFLOAT3(_posX, _posY, _posZ);
}

XMMATRIX TransformComponent::GetTranslationMatrix()
{
	return XMMatrixTranslation(_posX, _posY, _posZ);
}

XMFLOAT3 TransformComponent::GetRotation()
{
	return XMFLOAT3(_rotX, _rotY, _rotZ);
}

XMMATRIX TransformComponent::GetRotationMatrixX()
{
	return XMMatrixRotationX(_rotX);
}

XMFLOAT3 TransformComponent::GetScale()
{
	return XMFLOAT3(_scaX, _scaY, _scaZ);
}

XMMATRIX TransformComponent::GetScaleMatrix()
{
	return XMMatrixScaling(_scaX, _scaY, _scaZ);
}

#endif



