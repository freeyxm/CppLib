#include "stdafx.h"
#include "Vector3.h"
#include <cmath>

namespace cpplib
{
	namespace math
	{
		const Vector3 Vector3::zero(0, 0, 0);
		const Vector3 Vector3::one(1, 1, 1);
		const Vector3 Vector3::left(-1, 0, 0);
		const Vector3 Vector3::right(1, 0, 0);
		const Vector3 Vector3::up(0, 1, 0);
		const Vector3 Vector3::down(0, -1, 0);
		const Vector3 Vector3::forward(0, 0, 1);
		const Vector3 Vector3::back(0, 0, -1);
		const Vector3 Vector3::infinity(INFINITY, INFINITY, INFINITY);

		Vector3::Vector3()
			: x(0), y(0), z(0)
		{
		}

		Vector3::Vector3(float x, float y, float z)
			: x(x), y(y), z(z)
		{
		}

		Vector3::Vector3(const Vector3 & a)
			: x(a.x), y(a.y), z(a.z)
		{
		}

		Vector3 & Vector3::operator=(const Vector3 & a)
		{
			x = a.x;
			y = a.y;
			z = a.z;
			return *this;
		}

		Vector3 & Vector3::operator+=(const Vector3 & a)
		{
			x += a.x;
			y += a.y;
			z += a.z;
			return *this;
		}

		Vector3 & Vector3::operator-=(const Vector3 & a)
		{
			x -= a.x;
			y -= a.y;
			z -= a.z;
			return *this;
		}

		Vector3 & Vector3::operator*=(float n)
		{
			x *= n;
			y *= n;
			z *= n;
			return *this;
		}

		Vector3 & Vector3::operator/=(float n)
		{
			float oneOverN = 1.0f / n;
			x *= oneOverN;
			y *= oneOverN;
			z *= oneOverN;
			return *this;
		}

		Vector3 Vector3::operator-() const
		{
			return Vector3(-x, -y, -z);
		}

		Vector3 Vector3::operator+(const Vector3 & a) const
		{
			return Vector3(x + a.x, y + a.y, z + a.z);
		}

		Vector3 Vector3::operator-(const Vector3 & a) const
		{
			return Vector3(x - a.x, y - a.y, z - a.z);
		}

		Vector3 Vector3::operator*(float n) const
		{
			return Vector3(x * n, y * n, z * n);
		}

		Vector3 Vector3::operator/(float n) const
		{
			float oneOverN = 1.0f / n;
			return Vector3(x * oneOverN, y * oneOverN, z * oneOverN);
		}

		bool Vector3::operator==(const Vector3 & a) const
		{
			return IsEqual(x, a.x) && IsEqual(y, a.y) && IsEqual(z, a.z);
		}

		bool Vector3::operator!=(const Vector3 & a) const
		{
			return !IsEqual(x, a.x) || !IsEqual(y, a.y) || !IsEqual(z, a.z);
		}

		void Vector3::Zero()
		{
			x = y = z = 0;
		}

		void Vector3::Normalize()
		{
			float length = Length();
			if (length > 0.0f)
			{
				float oneOverN = 1.0f / length;
				x *= oneOverN;
				y *= oneOverN;
				z *= oneOverN;
			}
		}

		Vector3 Vector3::normalized() const
		{
			float length = Length();
			if (length > 0.0f)
			{
				float oneOverN = 1.0f / length;
				return Vector3(x*oneOverN, y*oneOverN, z*oneOverN);
			}
			else
			{
				return Vector3::infinity;
			}
		}

		float Vector3::Length() const
		{
			return sqrt(LengthSquared());
		}

		float Vector3::LengthSquared() const
		{
			return x * x + y * y + z * z;
		}

		Vector3 Vector3::Cross(const Vector3 & a, const Vector3 & b)
		{
			return Vector3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
		}

		float Vector3::Dot(const Vector3 & a, const Vector3 & b)
		{
			return a.x*b.x + a.y*b.y + a.z*b.z;
		}

		bool Vector3::IsEqual(float a, float b)
		{
			float diff = a - b;
			return -1E-5f < diff && diff < +1E-5f;
		}

		float Vector3::Distance(const Vector3 & a, const Vector3 & b)
		{
			return sqrt(DistanceSquared(a, b));
		}

		float Vector3::DistanceSquared(const Vector3 & a, const Vector3 & b)
		{
			float dx = a.x - b.x;
			float dy = a.y - b.y;
			float dz = a.z - b.z;
			return dx * dx + dy * dy + dz * dz;
		}
	} // namespace math
} // namespace cpplib