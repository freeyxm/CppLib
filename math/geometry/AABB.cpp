#include "AABB.h"
#include <limits>

namespace cpplib {
namespace math {
namespace geometry {

AABB::AABB(const Vector3& min, const Vector3& max)
    : m_min(min)
    , m_max(max)
{
}

AABB::~AABB()
{
}

void AABB::Reset()
{
    m_min.x = m_min.y = m_min.z = FLT_MAX;
    m_max.x = m_max.y = m_max.z = FLT_MIN;
}

void AABB::AddPoint(const Vector3 & point)
{
    if (m_min.x > point.x) m_min.x = point.x;
    if (m_max.x < point.x) m_max.x = point.x;
    if (m_min.y > point.y) m_min.y = point.y;
    if (m_max.y < point.y) m_max.y = point.y;
    if (m_min.z > point.z) m_min.z = point.z;
    if (m_max.z < point.z) m_max.z = point.z;
}

// @see https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
bool AABB::Raycast(const Ray & ray, float& tmin, float& tmax)
{
    Vector3 invdir(1.0f / ray.direction().x, 1.0f / ray.direction().y, 1.0f / ray.direction().z);
    float tminy, tmaxy, tminz, tmaxz;

    if (ray.origin().x >= 0) {
        tmin = (m_min.x - ray.origin().x) * invdir.x;
        tmax = (m_max.x - ray.origin().x) * invdir.x;
    }
    else {
        tmin = (m_max.x - ray.origin().x) * invdir.x;
        tmax = (m_min.x - ray.origin().x) * invdir.x;
    }

    if (ray.origin().y >= 0) {
        tminy = (m_min.y - ray.origin().y) * invdir.y;
        tmaxy = (m_max.y - ray.origin().y) * invdir.y;
    }
    else {
        tminy = (m_max.y - ray.origin().y) * invdir.y;
        tmaxy = (m_min.y - ray.origin().y) * invdir.y;
    }

    if (tmin > tmaxy || tmax < tminy) {
        return false;
    }

    if (tmin > tminy) tmin = tminy;
    if (tmax < tmaxy) tmax = tmaxy;

    if (ray.origin().z >= 0) {
        tminz = (m_min.z - ray.origin().z) * invdir.z;
        tmaxz = (m_max.z - ray.origin().z) * invdir.z;
    }
    else {
        tminz = (m_max.z - ray.origin().z) * invdir.z;
        tmaxz = (m_min.z - ray.origin().z) * invdir.z;
    }

    if (tmin > tmaxz || tmax < tminz) {
        return false;
    }

    if (tmin > tminz) tmin = tminz;
    if (tmax < tmaxz) tmax = tmaxz;

    return true;
}

Vector3 AABB::Center() const
{
    return (m_max + m_min) * 0.5f;
}

Vector3 AABB::Size() const
{
    return m_max - m_min;
}

} // namespace geometry
} // namespace math
} // namespace cpplib