#ifndef __CPPLIB_MATH_GEOMETRY_AABB_H__
#define __CPPLIB_MATH_GEOMETRY_AABB_H__
#include "math/Vector3.h"
#include "Ray.h"

namespace cpplib {
namespace math {
namespace geometry {

class AABB
{
public:
    AABB(const Vector3& min, const Vector3& max);
    ~AABB();

    void Reset();
    void AddPoint(const Vector3& point);

    bool Raycast(const Ray& ray, float& tmin, float& tmax);

    Vector3 Center() const;
    Vector3 Size() const;

private:
    Vector3 m_min;
    Vector3 m_max;
};

} // namespace geometry
} // namespace math
} // namespace cpplib
#endif // !__CPPLIB_MATH_GEOMETRY_AABB_H__
