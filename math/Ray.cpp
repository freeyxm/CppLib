#include "stdafx.h"
#include "Ray.h"

namespace cpplib {
namespace math {
namespace geometry {

Ray::Ray(const Vector3& origin, const Vector3& direction)
    : m_origin(origin)
    , m_direction(direction)
{
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
}

} // namespace geometry
} // namespace math
} // namespace cpplib
