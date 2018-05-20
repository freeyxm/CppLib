#include "stdafx.h"
#include "Matrix4x4.h"
#include "Math.h"
#include <cstring>
#include <cmath>
#include <assert.h>

#define swap(a, b, tmp) { tmp = a; a = b; b = tmp; }

namespace cpplib {
namespace math {

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
    assert(0 <= row && row <= N);
    return m[row];
}

const float * Matrix4x4::operator[](int row) const
{
    assert(0 <= row && row <= N);
    return m[row];
}

bool Matrix4x4::operator==(const Matrix4x4 & t) const
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!math::IsEqual(m[i][j], t.m[i][j]))
                return false;
        }
    }
    return true;
}

bool Matrix4x4::operator!=(const Matrix4x4 & t) const
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!math::IsEqual(m[i][j], t.m[i][j]))
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
    float row[N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            row[j] = m[i][0] * t.m[0][j] + m[i][1] * t.m[1][j] + m[i][2] * t.m[2][j] + m[i][3] * t.m[3][j];
        }
        m[i][0] = row[0];
        m[i][1] = row[1];
        m[i][2] = row[2];
        m[i][3] = row[3];
    }
    return *this;
}

Matrix4x4 & Matrix4x4::operator*=(float k)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            m[i][j] *= k;
        }
    }
    return *this;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & t) const
{
    Matrix4x4 matrix;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix.m[i][j] = m[i][0] * t.m[0][j] + m[i][1] * t.m[1][j] + m[i][2] * t.m[2][j] + m[i][3] * t.m[3][j];
        }
    }
    return matrix;
}

Matrix4x4 Matrix4x4::operator*(float k) const
{
    Matrix4x4 matrix;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix.m[i][j] = m[i][j] * k;
        }
    }
    return matrix;
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
    float w = m41 * v.x + m42 * v.y + m43 * v.z + m44;
    float w1 = 1.0f / w;
    return Vector3(x*w1, y*w1, z*w1);
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

// Scale in an Arbitrary Direction
Matrix4x4 Matrix4x4::Scale(const Vector3 & axis, float k)
{
    const Vector3 n = axis.normalized();
    const float   k1 = k - 1;
    const float  xk1 = n.x *  k1;
    const float xxk1 = n.x * xk1;
    const float xyk1 = n.y * xk1;
    const float xzk1 = n.z * xk1;
    const float  yk1 = n.y *  k1;
    const float yyk1 = n.y * yk1;
    const float yzk1 = n.z * yk1;
    const float zzk1 = n.z * n.z * k1;

    return Matrix4x4({
        1 + xxk1,     xyk1,     xzk1, 0,
            xyk1, 1 + yyk1,     yzk1, 0,
            xzk1,     yzk1, 1 + zzk1, 0,
               0,        0,        0, 1,
        });
}

Matrix4x4 Matrix4x4::Rotate(const Quaternion & q)
{
    float xx = q.x * q.x * 2;
    float xy = q.x * q.y * 2;
    float xz = q.x * q.z * 2;
    float yy = q.y * q.y * 2;
    float yz = q.y * q.z * 2;
    float zz = q.z * q.z * 2;
    float wx = q.w * q.x * 2;
    float wy = q.w * q.y * 2;
    float wz = q.w * q.z * 2;
    return Matrix4x4(
        1 - yy - zz, xy - wz, xz + wy, 0,
        xy + wz, 1 - xx - zz, yz - wx, 0,
        xz - wy, yz + wx, 1 - xx - yy, 0,
        0, 0, 0, 1
    );
}

Matrix4x4 Matrix4x4::Rotate(const Vector3 & axis, float degree)
{
    const Vector3 n = axis.normalized();
    const float radian = degree * math::Deg2Rad;
    const float c = cos(radian);
    const float s = sin(radian);
    const float   c1 = 1 - c;
    const float  xc1 = n.x * c1;
    const float xxc1 = n.x * xc1;
    const float xyc1 = n.y * xc1;
    const float xzc1 = n.z * xc1;
    const float  yc1 = n.y * c1;
    const float yyc1 = n.y * yc1;
    const float yzc1 = n.z * yc1;
    const float zzc1 = n.z * n.z * c1;
    const float   xs = n.x * s;
    const float   ys = n.y * s;
    const float   zs = n.z * s;

    return Matrix4x4({
        (xxc1 + c),  (xyc1 - zs), (xzc1 + ys), 0,
        (xyc1 + zs), (yyc1 + c),  (yzc1 - xs), 0,
        (xzc1 - ys), (yzc1 + xs), (zzc1 + c),  0,
                  0,           0,          0,  1,
        });
}

Matrix4x4 Matrix4x4::Rotate(const Vector3 & euler)
{
    const float h = euler.y * math::Deg2Rad;
    const float p = euler.x * math::Deg2Rad;
    const float b = euler.z * math::Deg2Rad;
    const float ch = cos(h);
    const float cp = cos(p);
    const float ch_cp = ch * cp;
    const float sp = sin(p);
    const float ch_sp = ch * sp;
    const float cb = cos(b);
    const float ch_cb = ch * cb;
    const float sb = sin(b);
    const float ch_sb = ch * sb;
    const float sh = sin(h);
    const float sh_sb = sh * sb;
    const float sh_cb = sh * cb;
    const float sh_sp = sh * sp;
    const float sh_cp = sh * cp;
    const float sb_cp = sb * cp;
    const float cb_cp = cb * cp;

    return Matrix4x4(
        ch_cb + sh_sp * sb, -ch_sb + sh_sp * cb, sh_cp, 0,
        sb_cp, cb_cp, -sp, 0,
        -sh_cb + ch_sp * sb, sh_sb + ch_cb * sp, ch_cp, 0,
        0, 0, 0, 1
    );
}

Matrix4x4 Matrix4x4::RotateX(float degree)
{
    const float radian = degree * math::Deg2Rad;
    const float c = cos(radian);
    const float s = sin(radian);
    return Matrix4x4({
         1, 0, 0, 0,
         0, c,-s, 0,
         0, s, c, 0,
         0, 0, 0, 1,
        });
}

Matrix4x4 Matrix4x4::RotateY(float degree)
{
    const float radian = degree * math::Deg2Rad;
    const float c = cos(radian);
    const float s = sin(radian);
    return Matrix4x4({
         c, 0, s, 0,
         0, 1, 0, 0,
        -s, 0, c, 0,
         0, 0, 0, 1,
        });
}

Matrix4x4 Matrix4x4::RotateZ(float degree)
{
    const float radian = degree * math::Deg2Rad;
    const float c = cos(radian);
    const float s = sin(radian);
    return Matrix4x4({
         c,-s, 0, 0,
         s, c, 0, 0,
         0, 0, 1, 0,
         0, 0, 0, 1,
        });
}

Matrix4x4 Matrix4x4::TRS(const Vector3 & t, const Vector3 & r, const Vector3 & s)
{
    Matrix4x4 matrix = Matrix4x4::Translate(t);
    matrix *= Matrix4x4::Rotate(r);
    matrix *= Matrix4x4::Scale(s);
    return matrix;
}

// Projecting onto an Arbitrary Line or Plane.
// Same with Scale(axis, 0);
Matrix4x4 Matrix4x4::ProjectOrtho(const Vector3 & axis)
{
    const Vector3 n = axis.normalized();
    float xx = n.x * n.x;
    float xy = n.x * n.y;
    float xz = n.x * n.z;
    float yy = n.y * n.y;
    float yz = n.y * n.z;
    float zz = n.z * n.z;
    return Matrix4x4(
        1 - xx, -xy, -xz, 0,
        -xy, 1 - yy, -yz, 0,
        -xz, -yz, 1 - zz, 0,
        0, 0, 0, 1
    );
}

// Reflection.
// Same with Scale(axis, -1);
Matrix4x4 Matrix4x4::Reflect(const Vector3 & axis)
{
    const Vector3 n = axis.normalized();
    float xx2 = n.x * n.x * 2;
    float xy2 = n.x * n.y * 2;
    float xz2 = n.x * n.z * 2;
    float yy2 = n.y * n.y * 2;
    float yz2 = n.y * n.z * 2;
    float zz2 = n.z * n.z * 2;
    return Matrix4x4(
        1 - xx2, -xy2, -xz2, 0,
        -xy2, 1 - yy2, -yz2, 0,
        -xz2, -yz2, 1 - zz2, 0,
        0, 0, 0, 1
    );
}

Matrix4x4 Matrix4x4::Ortho(float l, float r, float b, float t, float n, float f)
{
    float r_l = 1.0f / (r - l);
    float t_b = 1.0f / (t - b);
    float f_n = 1.0f / (f - n);
    return Matrix4x4(
        2 * r_l, 0, 0, -(r + l) * r_l,
        0, 2 * t_b, 0, -(t + b) * t_b,
        0, 0, -2 * f_n, -(f + n) * f_n,
        0, 0, 0, 1
    );
}

Matrix4x4 Matrix4x4::Perspective(float l, float r, float b, float t, float n, float f)
{
    float r_l = 1.0f / (r - l);
    float t_b = 1.0f / (t - b);
    float f_n = 1.0f / (f - n);
    float n_2 = n * 2;
    return Matrix4x4(
        n_2 * r_l, 0, (r + l) * r_l, 0,
        0, n_2 * t_b, (t + b) * t_b, 0,
        0, 0, (-f - n) * f_n, -n_2 * f * f_n,
        0, 0, -1, 0
    );
}

Matrix4x4 Matrix4x4::Perspective(float fov, float aspect, float n, float f)
{
    float tf = 1.0f / tan(fov * math::Deg2Rad * 0.5f);
    float f_n = 1.0f / (f - n);
    return Matrix4x4(
        tf / aspect, 0, 0, 0,
        0, tf, 0, 0,
        0, 0, (-f - n) * f_n, (-2 * n * f * f_n),
        0, 0, -1, 0
    );
}

float Matrix4x4::Determinant() const
{
    float m31_m42 = m31 * m42;
    float m31_m43 = m31 * m43;
    float m31_m44 = m31 * m44;

    float m32_m44 = m32 * m44;
    float m32_m43 = m32 * m43;
    float m32_m41 = m32 * m41;

    float m33_m41 = m33 * m41;
    float m33_m44 = m33 * m44;
    float m33_m42 = m33 * m42;

    float m34_m42 = m34 * m42;
    float m34_m41 = m34 * m41;
    float m34_m43 = m34 * m43;

    float m1 = m11 * (m22 * (m33_m44 - m34_m43) + m23 * (m34_m42 - m32_m44) + m24 * (m32_m43 - m33_m42));
    float m2 = m12 * (m21 * (m33_m44 - m34_m43) + m23 * (m34_m41 - m31_m44) + m24 * (m31_m43 - m33_m41));
    float m3 = m13 * (m21 * (m32_m44 - m34_m42) + m22 * (m34_m41 - m31_m44) + m24 * (m31_m42 - m32_m41));
    float m4 = m14 * (m21 * (m32_m43 - m33_m42) + m22 * (m33_m41 - m31_m43) + m23 * (m31_m42 - m32_m41));

    float mm = m1 - m2 + m3 - m4;
    return mm;
}

Matrix4x4 Matrix4x4::Inverse() const
{
    Matrix4x4 a(*this);
    Matrix4x4 b(Matrix4x4::identity);
    // bottom
    for (int i = 0; i < N; ++i) {
        if (math::IsEqual(m[i][i], 0)) {
            bool find = false;
            for (int j = i + 1; j < N; ++j) {
                if (!math::IsEqual(m[j][i], 0)) {
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
        if (!math::IsEqual(a.m[i][i], 1))
        {
            float k = 1.0f / a.m[i][i];
            //a.MulRow(i, k);
            a.m[i][i] = 1;
            for (int c = i + 1; c < N; ++c)
            {
                a.m[i][c] *= k;
            }
            b.MulRow(i, k);
        }
        for (int j = i + 1; j < N; ++j)
        {
            float k = -a.m[j][i];
            if (!math::IsEqual(k, 0))
            {
                //a.AddRow(j, i, k);
                a.m[j][i] = 0;
                for (int c = i + 1; c < N; ++c)
                {
                    a.m[j][c] += a.m[i][c] * k;
                }
                b.AddRow(j, i, k);
            }
        }
    }
    // top
    for (int i = N - 1; i > 0; --i)
    {
        for (int j = i - 1; j >= 0; --j)
        {
            float k = -a.m[j][i];
            if (!math::IsEqual(k, 0))
            {
                //a.AddRow(j, i, k);
                a[j][i] = 0;
                b.AddRow(j, i, k);
            }
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

Quaternion Matrix4x4::Rotation() const
{
    float w2 = m11 + m22 + m33;
    float x2 = m11 - m22 - m33;
    float y2 = m22 - m11 - m33;
    float z2 = m33 - m11 - m22;

    float max = w2;
    int index = 0;
    if (max < x2) {
        max = x2;
        index = 1;
    }
    if (max < y2) {
        max = y2;
        index = 2;
    }
    if (max < z2) {
        max = z2;
        index = 3;
    }

    float max_value = sqrt(max + 1) * 0.5f;
    float mult = 0.25f / max_value;
    switch (index)
    {
    case 0:
        return Quaternion((m32 - m23)*mult, (m13 - m31)*mult, (m21 - m12)*mult, max_value);
    case 1:
        return Quaternion(max_value, (m12 + m21)*mult, (m31 + m13)*mult, (m32 - m23)*mult);
    case 2:
        return Quaternion((m12 + m21)*mult, max_value, (m23 + m32)*mult, (m13 - m31)*mult);
    case 3:
        return Quaternion((m31 + m13)*mult, (m23 + m32)*mult, max_value, (m21 - m12)*mult);
    default:
        return Quaternion();
    }
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

void Matrix4x4::MulRow(int r, float k)
{
    for (int i = 0; i < N; ++i)
    {
        m[r][i] *= k;
    }
}

} // namespace math
} // namespace cpplib
