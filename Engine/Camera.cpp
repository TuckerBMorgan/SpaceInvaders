#include "Camera.h"

Camera::Camera()
{

	m_poisitonX = 0;
	m_positionY = 0;
	m_positionZ = 0;

	m_rotationX = 0;
	m_rotationY = 0;
	m_rotationZ = 0;

	m_viewMatrix = XMMATRIX();
	up = position = lookAt = XMFLOAT3();
	upVector = positionVector = lookAtVector = XMVECTOR();

	rotationMatrix = XMMATRIX();
}

Camera::~Camera()
{

}

void* Camera::operator new(unsigned int memeorysize)
{
	unsigned int aligment;
	void* memoryBlockPtr;

	aligment = 16;
	memoryBlockPtr = _aligned_malloc(memeorysize, aligment);

	return memoryBlockPtr;
}

void Camera::operator delete(void* memoryBlockPtr)
{
	_aligned_free(memoryBlockPtr);
}

void Camera::SetPosition(float x, float y, float z)
{
	m_poisitonX = x;
	m_positionY = y;
	m_positionZ = z;
}

void Camera::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
}

XMFLOAT3 Camera::GetPosition()
{
	return XMFLOAT3(m_poisitonX, m_positionY, m_positionZ);
}
XMFLOAT3 Camera::GetRotation()
{
	return XMFLOAT3(m_rotationX, m_rotationY, m_rotationZ);
}

void Camera::Render()
{

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Load it into a XMVECTOR structure.
	upVector = XMLoadFloat3(&up);

	// Setup the position of the camera in the world.
	position.x = m_poisitonX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Load it into a XMVECTOR structure.
	positionVector = XMLoadFloat3(&position);

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Load it into a XMVECTOR structure.
	lookAtVector = XMLoadFloat3(&lookAt);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}

void Camera::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}


