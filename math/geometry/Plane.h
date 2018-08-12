#ifndef __CPPLIB_MATH_GEOMETRY_PLANE_H__
#define __CPPLIB_MATH_GEOMETRY_PLANE_H__
#include "../Vector3.h"
#include "Ray.h"

namespace cpplib {
namespace math {
namespace geometry {

class Plane
{
public:
    Plane(const Vector3& normal, float d);
    Plane(const Vector3& normal, const Vector3& point);
    Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3);
    Plane(const Plane& plane);
    ~Plane();

    void Set(const Vector3& normal, float d);
    void Set(const Vector3& normal, const Vector3& point);
    void Set(const Vector3& p1, const Vector3& p2, const Vector3& p3);

    Vector3 normal() const { return m_normal; };
    float distance() const { return m_distance; };

    float Distance(const Vector3& point);
    Vector3 ClosestPoint(const Vector3& point);

    bool GetSide(const Vector3& point);

    bool Raycast(const Ray& ray, float& t);

private:
    Vector3 m_normal;
    float m_distance;
};

} // namespace geometry
} // namespace math
} // namespace cpplib
#endif // !__CPPLIB_MATH_GEOMETRY_PLANE_H__
