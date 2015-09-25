#pragma once

struct Vector3
{
	Vector3(float inX, float inY, float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	};
	float x;
	float y;
	float z;
	Vector3 operator+=(Vector3 const& second)
	{
		x += second.x;
		y += second.y;
		z += second.z;
		return Vector3(x,y,z);
	}

	Vector3 operator-=(Vector3 const& second)
	{
		x -= second.x;
		y -= second.y;
		z -= second.z;
		return Vector3(x, y, z);
	}
	/*
#if _DX_
	Vector3 operator*(XMMATRIX const& other)
	{
		XMFLOAT4X4 use = XMFLOAT4X4();
		XMStoreFloat4x4(&use, other);

		float col1 = (x * use._11) + (y * use._21) + (z * use._31);

		return Vector3(0, 0, 0);
	}
#endif
will be done when a more complex collision system is nessacary 
*/
};