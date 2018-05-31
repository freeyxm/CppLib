#include "stdafx.h"
#include "Plane.h"
#include "Math.h"

namespace cpplib {
namespace math {
namespace geometry {

Plane::Plane(const Vector3& normal, float d)
    : m_normal(normal)
    , m_distance(d)
{
    m_normal.Normalize();
}

Plane::Plane(const Vector3& normal, const Vector3& point)
    : m_normal(normal)
{
    m_normal.Normalize();
    m_distance = Vector3::Dot(normal, point);
}

Plane::Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3)
{
    Set(p1, p2, p3);
}

Plane::Plane(const Plane & plane)
{
    m_normal = plane.m_normal;
    m_distance = plane.m_distance;
}


Plane::~Plane()
{
}

void Plane::Set(const Vector3 & normal, const Vector3 & point)
{
    m_normal = normal;
    m_normal.Normalize();
    m_distance = Vector3::Dot(normal, point);
}

void Plane::Set(const Vector3 & normal, float d)
{
    m_normal = normal;
    m_normal.Normalize();
    m_distance = d;
}

void Plane::Set(const Vector3 & p1, const Vector3 & p2, const Vector3 & p3)
{
    m_normal = Vector3::Cross(p2 - p1, p3 - p2);
    m_normal.Normalize();
    m_distance = Vector3::Dot(m_normal, p1);
}

float Plane::Distance(const Vector3 & point)
{
    float distance = Vector3::Dot(point, m_normal) - m_distance;
    return distance;
}

Vector3 Plane::ClosestPoint(const Vector3 & point)
{
    Vector3 clp = point;
    clp += m_normal * (m_distance - Vector3::Dot(point, m_normal));
    return clp;
}

bool Plane::GetSide(const Vector3 & point)
{
    return Distance(point) >= 0;
}

bool Plane::Raycast(const Ray & ray, float & t)
{
    float dot = Vector3::Dot(ray.direction(), this->m_normal);
    if (math::IsEqual(dot, 0))
    {
        t = 0;
        return false;
    }
    t = (this->m_distance - Vector3::Dot(ray.origin(), this->m_normal)) / dot;
    return t >= 0;
}

} // namespace geometry
} // namespace math
} // namespace cpplib