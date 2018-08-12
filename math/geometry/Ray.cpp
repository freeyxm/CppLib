#include "Ray.h"
#include "math/Math.h"

namespace cpplib {
namespace math {
namespace geometry {

Ray::Ray(const Vector3& origin, const Vector3& direction)
    : m_origin(origin)
    , m_direction(direction)
{
    m_direction.Normalize();
}

Ray::Ray(const Ray & ray)
    : m_origin(ray.m_origin)
    , m_direction(ray.m_direction)
{
}

Ray::~Ray()
{
}

void Ray::Set(const Vector3& origin, const Vector3& direction)
{
    m_origin = origin;
    m_direction = direction;
    m_direction.Normalize();
}

bool Ray::Raycast(const Ray & ray2, float & t1, float & t2)
{
    Vector3 cross = Vector3::Cross(this->m_direction, ray2.m_direction);
    float length2 = cross.LengthSquared();
    if (math::IsEqual(length2, 0)) {
        t1 = t2 = 0;
        return false;
    }

    float oneOverLen2 = 1.0f / length2;
    Vector3 p = ray2.m_origin - this->m_origin;
    t1 = Vector3::Dot(Vector3::Cross(p, ray2.m_direction), cross) * oneOverLen2;
    t2 = Vector3::Dot(Vector3::Cross(p, this->m_direction), cross) * oneOverLen2;
    if (t1 < 0 || t2 < 0) {
        return false;
    }

    Vector3 p1 = this->m_origin + this->m_direction * t1;
    Vector3 p2 = ray2.m_origin + ray2.m_direction * t2;
    float distance2 = (p1 - p2).LengthSquared();
    return math::IsEqual(distance2, 0);
}

} // namespace geometry
} // namespace math
} // namespace cpplib
