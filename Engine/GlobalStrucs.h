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
	
};