#include "stdafx.h"
#include "Matrix4x4.h"
#include "Math.h"
#include <cstring>
#include <cmath>
#include <assert.h>

#define swap(a, b, tmp) { tmp = a; a = b; b = tmp; }

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

        Matrix4x4::Matrix4x4(
            float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44)
            : m11(m11), m12(m12), m13(m13), m14(m14)
            , m21(m21), m22(m22), m23(m23), m24(m24)
            , m31(m31), m32(m32), m33(m33), m34(m34)
            , m41(m41), m42(m42), m43(m43), m44(m44)
        {
        }

        float * Matrix4x4::operator[](int row)
        {
            assert(0 <= row && row <= 4);
            return m[row];
        }

        const float * Matrix4x4::operator[](int row) const
        {
            assert(0 <= row && row <= 4);
            return m[row];
        }

        bool Matrix4x4::operator==(const Matrix4x4 & t) const
        {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (!Math::IsEqual(m[i][j], t.m[i][j]))
                        return false;
                }
            }
            return true;
        }

        bool Matrix4x4::operator!=(const Matrix4x4 & t) const
        {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (!Math::IsEqual(m[i][j], t.m[i][j]))
                        return true;
                }
            }
            return false;
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

        Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & t) const
        {
            Matrix4x4 matrix;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    matrix.m[i][j] = m[i][0] * t.m[0][j] + m[i][1] * t.m[1][j] + m[i][2] * t.m[2][j] + m[i][3] * t.m[3][j];
                }
            }
            return matrix;
        }

        Vector3 Matrix4x4::operator*(const Vector3 & v) const
        {
            return this->MultiplyPoint(v);
        }

        Vector3 Matrix4x4::MultiplyVector(const Vector3 & v) const
        {
            float x = m11 * v.x + m12 * v.y + m13 * v.z;
            float y = m21 * v.x + m22 * v.y + m23 * v.z;
            float z = m31 * v.x + m32 * v.y + m33 * v.z;
            return Vector3(x, y, z);
        }

        Vector3 Matrix4x4::MultiplyPoint(const Vector3 & v) const
        {
            float x = m11 * v.x + m12 * v.y + m13 * v.z + m14;
            float y = m21 * v.x + m22 * v.y + m23 * v.z + m24;
            float z = m31 * v.x + m32 * v.y + m33 * v.z + m34;
            return Vector3(x, y, z);
        }

        Matrix4x4 Matrix4x4::Translate(const Vector3 & v)
        {
            return Matrix4x4({
                  1,   0,   0,   v.x,
                  0,   1,   0,   v.y,
                  0,   0,   1,   v.z,
                  0,   0,   0,     1,
                });
        }

        Matrix4x4 Matrix4x4::Scale(const Vector3& s)
        {
            return Matrix4x4({
                s.x,   0,   0,   0,
                  0, s.y,   0,   0,
                  0,   0, s.z,   0,
                  0,   0,   0,   1,
                });
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
                (xxc1 + c),  (xyc1 - zs), (xzc1 + ys), 0,
                (xyc1 + zs), (yyc1 + c),  (yzc1 - xs), 0,
                (xzc1 - ys), (yzc1 + xs),  (zzc1 + c), 0,
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
                 0, c,-s, 0,
                 0, s, c, 0,
                 0, 0, 0, 1,
                });
        }

        Matrix4x4 Matrix4x4::RotateY(float angle)
        {
            float radius = angle * Math::Deg2Rad;
            float c = cos(radius);
            float s = sin(radius);
            return Matrix4x4({
                 c, 0, s, 0,
                 0, 1, 0, 0,
                -s, 0, c, 0,
                 0, 0, 0, 1,
                });
        }

        Matrix4x4 Matrix4x4::RotateZ(float angle)
        {
            float radius = angle * Math::Deg2Rad;
            float c = cos(radius);
            float s = sin(radius);
            return Matrix4x4({
                 c,-s, 0, 0,
                 s, c, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1,
                });
        }

        float Matrix4x4::Determinant() const
        {
            return
                m11 * (m22 * (m33 * m33 - m34 * m43) - m23 * (m34 * m42 + m32 * m44) + m24 * (m32 * m43 - m33 * m42)) -
                m21 * (m12 * (m33 * m44 - m34 * m43) - m23 * (m34 * m41 + m31 * m44) + m24 * (m31 * m43 - m33 * m41)) +
                m31 * (m21 * (m32 * m44 - m34 * m42) - m22 * (m34 * m41 + m31 * m44) + m42 * (m13 * m24 - m14 * m23)) -
                m41 * (m12 * (m23 * m34 - m24 * m33) - m22 * (m13 * m34 + m14 * m33) + m32 * (m13 * m24 - m14 * m23));
        }

        Matrix4x4 Matrix4x4::Inverse() const
        {
            Matrix4x4 a(*this);
            Matrix4x4 b(Matrix4x4::identity);
            // bottom
            for (int i = 0; i < N; ++i) {
                if (Math::IsEqual(m[i][i], 0)) {
                    bool find = false;
                    for (int j = i + 1; j < N; ++j) {
                        if (!Math::IsEqual(m[j][i], 0)) {
                            a.SwapRow(i, j);
                            b.SwapRow(i, j);
                            find = true;
                            break;
                        }
                    }
                    if (!find) {
                        return Matrix4x4::zero;
                    }
                }
                float factor = 1.0f / a.m[i][i];
                for (int c = i; c < N; ++c)
                {
                    a.m[i][c] *= factor;
                    b.m[i][c] *= factor;
                }
                for (int j = i + 1; j < N; ++j)
                {
                    float k = -a.m[j][i];
                    a.AddRow(j, i, k);
                    b.AddRow(j, i, k);
                }
            }
            // top
            for (int i = N - 1; i > 0; --i)
            {
                for (int j = i - 1; j >= 0; --j)
                {
                    float k = -a.m[j][i];
                    a.AddRow(j, i, k);
                    b.AddRow(j, i, k);
                }
            }
            return b;
        }

        Matrix4x4 Matrix4x4::Transpose() const
        {
            return Matrix4x4(
                m11, m21, m31, m41,
                m12, m22, m32, m42,
                m13, m23, m33, m43,
                m14, m24, m34, m44
            );
        }

        void Matrix4x4::SwapRow(int r1, int r2)
        {
            float tmp;
            for (int i = 0; i < N; ++i)
            {
                swap(m[r1][i], m[r2][i], tmp);
            }
        }

        void Matrix4x4::AddRow(int r1, int r2, float k)
        {
            for (int i = 0; i < N; ++i)
            {
                m[r1][i] += m[r2][i] * k;
            }
        }
    } // namespace math
} // namespace cpplib