#pragma once

#include <cmath>
#include <numbers>

struct Vector2
{
	float x, y;
	float Magnitude() const {
		return std::sqrt(x * x + y * y);
	}

	Vector2 operator-(const Vector2& other) const
	{
		return Vector2{ x - other.x, y - other.y };
	}

	Vector2 operator+(const Vector2& other) const
	{
		return Vector2{ x + other.x, y + other.y };
	}

	// You may also want to implement a constructor
	Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
};


struct Vector3
{
	float x, y, z;

	Vector3 operator*(float scalar) const {
		return Vector3{ x * scalar, y * scalar, z * scalar };
	}

	Vector3 operator+(Vector3 other)
	{
		return { this->x + other.x, this->y + other.y, this->z + other.z };
	}
	Vector3 operator-(Vector3 other)
	{
		return { this->x - other.x, this->y - other.y, this->z - other.z };
	}

	Vector3 operator/(float scalar) const
	{
		return { this->x / scalar, this->y / scalar, this->z / scalar };
	}

	Vector3 RelativeAngle()
	{
		return {
			std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
			std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
			0.0f
		};
	}

	inline float AngleDifference(const Vector3& other) const
	{
		auto deltaPitch = std::fabs(x - other.x);
		auto deltaYaw = std::fabs(y - other.y);

		if (deltaPitch > 180.0f)
			deltaPitch = 360.0f - deltaPitch;

		if (deltaYaw > 180.0f)
			deltaYaw = 360.0f - deltaYaw;

		return std::sqrt(deltaPitch * deltaPitch + deltaYaw * deltaYaw);
	}

	float Magnitude()  {
		return sqrt(x * x + y * y + z * z);
	}
};

struct Vector4
{
	float w, x, y, z;
};


float distance(Vector3 p1, Vector3 p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

