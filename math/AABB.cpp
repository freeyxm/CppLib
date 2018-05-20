#include "stdafx.h"
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

} // namespace geometry
} // namespace math
} // namespace cpplib