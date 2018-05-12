#include "stdafx.h"
#include "Matrix4x4.h"
#include "Math.h"
#include <cstring>
#include <cmath>
#include <assert.h>

namespace cpplib
{
	namespace math
	{
		const Matrix4x4 Matrix4x4::zero;
		const Matrix4x4 Matrix4x4::identity({
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
			});

		Matrix4x4::Matrix4x4()
		{
			memset(&m, 0, sizeof(m));
		}

		Matrix4x4::Matrix4x4(const Matrix4x4 & t)
		{
			memcpy_s(&m, sizeof(m), &t.m, sizeof(t.m));
		}

		Matrix4x4::Matrix4x4(float const (&a)[16])
		{
			assert(sizeof(m) == sizeof(a));
			memcpy_s(&m, sizeof(m), &a, sizeof(a));
		}

		float & Matrix4x4::operator[](int index)
		{
			assert(0 <= index && index < 16);
			return m[(index >> 2)][(index & 0x03)];
		}

		Matrix4x4 & Matrix4x4::operator=(const Matrix4x4 & t)
		{
			memcpy_s(&m, sizeof(m), &t.m, sizeof(t.m));
			return *this;
		}

		Matrix4x4& Matrix4x4::operator*=(const Matrix4x4 & t)
		{
			float row[4];
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					row[j] = m[i][0] * t.m[0][j] + m[i][1] * t.m[1][j] + m[i][2] * t.m[2][j] + m[i][3] * t.m[3][j];
				}
				m[i][0] = row[0];
				m[i][1] = row[1];
				m[i][2] = row[2];
				m[i][3] = row[3];
			}
			return *this;
		}

		Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & t)
		{
			Matrix4x4 matrix;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					matrix.m[i][j] = m[i][0] * t.m[0][j] + m[i][1] * t.m[1][j] + m[i][2] * t.m[2][j] + m[i][3] * t.m[3][j];
				}
			}
			return matrix;
		}

		Vector3 Matrix4x4::MultiplyVector(const Vector3 & v)
		{
			float x = v.x * m[0][0] + v.y *m[1][0] + v.z*m[2][0];
			float y = v.x * m[0][1] + v.y *m[1][1] + v.z*m[2][1];
			float z = v.x * m[0][2] + v.y *m[1][2] + v.z*m[2][2];
			return Vector3(x, y, z);
		}

		Vector3 Matrix4x4::MultiplyPoint(const Vector3 & v)
		{
			float x = v.x * m[0][0] + v.y *m[1][0] + v.z*m[2][0] + m[3][0];
			float y = v.x * m[0][1] + v.y *m[1][1] + v.z*m[2][1] + m[3][1];
			float z = v.x * m[0][2] + v.y *m[1][2] + v.z*m[2][2] + m[3][2];
			return Vector3(x, y, z);
		}

		Matrix4x4 Matrix4x4::Scale(const Vector3& scale)
		{
			Matrix4x4 matrix = Matrix4x4::identity;
			matrix.m[0][0] = scale.x;
			matrix.m[1][1] = scale.y;
			matrix.m[2][2] = scale.z;
			return matrix;
		}

		Matrix4x4 Matrix4x4::Scale(const Vector3 & n, float k)
		{
			float   k1 = k - 1;
			float  xk1 = n.x *  k1;
			float xxk1 = n.x * xk1;
			float xyk1 = n.y * xk1;
			float xzk1 = n.z * xk1;
			float  yk1 = n.y *  k1;
			float yyk1 = n.y * yk1;
			float yzk1 = n.z * yk1;
			float zzk1 = n.z * n.z * k1;

			return Matrix4x4({
				1 + xxk1,     xyk1,     xzk1, 0,
					xyk1, 1 + yyk1,     yzk1, 0,
					xzk1,     yzk1, 1 + zzk1, 0,
					   0,        0,        0, 1,
				});
		}

		Matrix4x4 Matrix4x4::Rotate(const Vector3 & n, float angle)
		{
			float radius = angle * Math::Deg2Rad;
			float c = cos(radius);
			float s = sin(radius);
			float c1 = 1 - c;
			float  xc1 = n.x * c1;
			float xxc1 = n.x * xc1;
			float xyc1 = n.y * xc1;
			float xzc1 = n.z * xc1;
			float  yc1 = n.y * c1;
			float yyc1 = n.y * yc1;
			float yzc1 = n.z * yc1;
			float zzc1 = n.z * n.z * c1;
			float   xs = n.x * s;
			float   ys = n.y * s;
			float   zs = n.z * s;

			return Matrix4x4({
				(xxc1 + c),  (xyc1 + zs), (xzc1 - ys), 0,
				(xyc1 - zs),  (yyc1 + c), (yzc1 + xs), 0,
				(xzc1 + ys), (yzc1 - xs),  (zzc1 + c), 0,
						  0,           0,           0, 1,
				});
		}

		Matrix4x4 Matrix4x4::Rotate(const Vector3 & euler)
		{
			return Matrix4x4();
		}

		Matrix4x4 Matrix4x4::RotateX(float angle)
		{
			float radius = angle * Math::Deg2Rad;
			float c = cos(radius);
			float s = sin(radius);
			return Matrix4x4({
				 1, 0, 0, 0,
				 0, c, s, 0,
				 0,-s, c, 0,
				 0, 0, 0, 1,
				});
		}

		Matrix4x4 Matrix4x4::RotateY(float angle)
		{
			float radius = angle * Math::Deg2Rad;
			float c = cos(radius);
			float s = sin(radius);
			return Matrix4x4({
				 c, 0,-s, 0,
				 0, 1, 0, 0,
				 s, 0, c, 0,
				 0, 0, 0, 1,
				});
		}

		Matrix4x4 Matrix4x4::RotateZ(float angle)
		{
			float radius = angle * Math::Deg2Rad;
			float c = cos(radius);
			float s = sin(radius);
			return Matrix4x4({
				 c, s, 0, 0,
				-s, c, 0, 0,
				 0, 0, 1, 0,
				 0, 0, 0, 1,
				});
		}
	} // namespace math
} // namespace cpplib
