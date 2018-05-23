#include "stdafx.h"
#include "Sphere.h"
#include "Math.h"
#include <cmath>

namespace cpplib {
namespace math {
namespace geometry {

Sphere::Sphere(Vector3 center, float radius)
    : m_center(center)
    , m_radius(radius)
{
}


Sphere::~Sphere()
{
}

void Sphere::Set(Vector3 center, float radius)
{
    m_center = center;
    m_radius = radius;
}

bool Sphere::Raycast(const Ray & ray, float & t)
{
    Vector3 vec = m_center - ray.origin();
    float a = Vector3::Dot(vec, ray.direction());
    float e = Vector3::Dot(vec, vec);
    float sqr = m_radius * m_radius - e * e + a * a;
    if (sqr < 0)
    {
        return false;
    }
    t = a - sqrt(sqr);
    return true;
}

} // namespace geometry
} // namespace math
} // namespace cpplib
