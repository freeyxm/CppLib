#include "stdafx.h"
#include "Triangle.h"
#include "Math.h"
#include <cmath>

namespace cpplib {
namespace math {
namespace geometry {

Triangle::Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3)
    : v1(v1), v2(v2), v3(v3)
{
}


Triangle::~Triangle()
{
}

void Triangle::Set(const Vector3 & v1, const Vector3 & v2, const Vector3 & v3)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
}

bool Triangle::Raycast(const Ray & ray, float minT, float & t)
{
    Vector3 e3 = v2 - v1;
    Vector3 e1 = v3 - v2;
    Vector3 n = Vector3::Cross(e3, e1);
    float dot = Vector3::Dot(n, ray.direction());
    if (!(dot < 0.0f)) // NAN
    {
        return false;
    }
    float d = Vector3::Dot(n, v1);
    t = d - Vector3::Dot(n, ray.origin());
    if (!(t <= 0.0f)) // backside
    {
        return false;
    }
    if (!(t >= dot * minT)) // dot < 0
    {
        return false;
    }

    t /= dot;
    Vector3 p = ray.origin() + ray.direction() * t;

    float u0, u1, u2;
    float v0, v1, v2;
    if (fabs(n.x) > fabs(n.y))
    {
        if (fabs(n.x) > fabs(n.z))
        {
            u0 = p.y - this->v1.y;
            u1 = this->v2.y - this->v1.y;
            u2 = this->v3.y - this->v1.y;
            v0 = p.z - this->v1.z;
            v1 = this->v2.z - this->v1.z;
            v2 = this->v3.z - this->v1.z;
        }
        else
        {
            u0 = p.x - this->v1.x;
            u1 = this->v2.x - this->v1.x;
            u2 = this->v3.x - this->v1.x;
            v0 = p.y - this->v1.y;
            v1 = this->v2.y - this->v1.y;
            v2 = this->v3.y - this->v1.y;
        }
    }
    else
    {
        if (fabs(n.y) > fabs(n.z))
        {
            u0 = p.x - this->v1.x;
            u1 = this->v2.x - this->v1.x;
            u2 = this->v3.x - this->v1.x;
            v0 = p.z - this->v1.z;
            v1 = this->v2.z - this->v1.z;
            v2 = this->v3.z - this->v1.z;
        }
        else
        {
            u0 = p.x - this->v1.x;
            u1 = this->v2.x - this->v1.x;
            u2 = this->v3.x - this->v1.x;
            v0 = p.y - this->v1.y;
            v1 = this->v2.y - this->v1.y;
            v2 = this->v3.y - this->v1.y;
        }
    }
    float denom = u1 * v2 - v1 * u2;
    if (math::IsEqual(denom, 0.0f))
    {
        return false;
    }
    float oneOverDenom = 1.0f / denom;
    float b0 = (u0 * v2 - v0 * u2) * oneOverDenom;
    if (!(b0 >= 0.0f))
    {
        return false;
    }
    float b1 = (u1 * v0 - v1 * u0) * oneOverDenom;
    if (!(b1 >= 0.0f))
    {
        return false;
    }
    float b2 = 1.0f - b0 - b1;
    if (!(b2 >= 0.0f))
    {
        return false;
    }
    return true;
}

bool Triangle::GetBarycentricCoords(const Vector3& p, Vector3 & res)
{
    Vector3 e3 = this->v2 - this->v1;
    Vector3 e1 = this->v3 - this->v2;
    Vector3 n = Vector3::Cross(e3, e1);
    float ax = fabs(n.x);
    float ay = fabs(n.y);
    float az = fabs(n.z);
    float u1, u2, u3, u4;
    float v1, v2, v3, v4;
    if (ax >= ay && ax >= az)
    {
        // 投影到yz平面
        u1 = this->v1.y - this->v3.y;
        u2 = this->v2.y - this->v3.y;
        u3 = p.y - this->v1.y;
        u4 = p.y - this->v3.y;
        v1 = this->v1.z - this->v3.z;
        v2 = this->v2.z - this->v3.z;
        v3 = p.z - this->v1.z;
        v4 = p.z - this->v3.z;
    }
    else if (ay >= az)
    {
        // 投影到xz平面
        u1 = this->v1.z - this->v3.z;
        u2 = this->v2.z - this->v3.z;
        u3 = p.z - this->v1.z;
        u4 = p.z - this->v3.z;
        v1 = this->v1.x - this->v3.x;
        v2 = this->v2.x - this->v3.x;
        v3 = p.x - this->v1.x;
        v4 = p.x - this->v3.x;
    }
    else
    {
        // 投影到xy平面
        u1 = this->v1.x - this->v3.x;
        u2 = this->v2.x - this->v3.x;
        u3 = p.x - this->v1.x;
        u4 = p.x - this->v3.x;
        v1 = this->v1.y - this->v3.y;
        v2 = this->v2.y - this->v3.y;
        v3 = p.y - this->v1.y;
        v4 = p.y - this->v3.y;
    }
    float denom = v1 * u2 - v2 * u1;
    if (math::IsEqual(denom, 0.0f))
    {
        return false;
    }
    float oneOverDenom = 1.0f / denom;
    res.x = (v4 * u2 - v2 * u4) * oneOverDenom;
    res.y = (v1 * u3 - v3 * u1) * oneOverDenom;
    res.z = 1.0f - v1 - v2;
    return true;
}

float Triangle::Area() const
{
    Vector3 e1 = v3 - v2;
    Vector3 e2 = v1 - v3;
    Vector3 n = Vector3::Cross(v1, v2);
    float area = n.Length() * 0.5f;
    return area;
}

} // namespace geometry
} // namespace math
} // namespace cpplib
