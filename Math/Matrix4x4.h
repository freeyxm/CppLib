#pragma once
#include "Vector3.h"

namespace cpplib
{
	namespace math
	{
		struct Matrix4x4
		{
		public:
			Matrix4x4();
			Matrix4x4(const Matrix4x4& t);
			Matrix4x4(float const (&t)[16]);

			float& operator[](int index);

			Matrix4x4& operator=(const Matrix4x4& t);
			Matrix4x4& operator*=(const Matrix4x4& t);

			Matrix4x4 operator*(const Matrix4x4& t);

			Vector3 MultiplyVector(const Vector3& v);
			Vector3 MultiplyPoint(const Vector3& v);

			static Matrix4x4 Scale(const Vector3& scale);
			static Matrix4x4 Scale(const Vector3& axis, float scale);

			static Matrix4x4 Rotate(const Vector3& axis, float angle);
			static Matrix4x4 Rotate(const Vector3& euler);
			static Matrix4x4 RotateX(float angle);
			static Matrix4x4 RotateY(float angle);
			static Matrix4x4 RotateZ(float angle);

		public:
			const static Matrix4x4 identity;
			const static Matrix4x4 zero;

		private:
			float m[4][4];
		};
	} // namespace math
} // namespace cpplib
