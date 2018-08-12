#ifndef __CPPLIB_MATH_GEOMETRY_RAY_H__
#define __CPPLIB_MATH_GEOMETRY_RAY_H__
#include "../Vector3.h"

namespace cpplib {
namespace math {
namespace geometry {

class Ray
{
public:
    Ray(const Vector3& origin, const Vector3& direction);
    Ray(const Ray& ray);
    ~Ray();

    void Set(const Vector3& origin, const Vector3& direction);

    Vector3 origin() const { return m_origin; };
    Vector3 direction() const { return m_direction; };

    bool Raycast(const Ray& ray2, float& t1, float& t2);

private:
    Vector3 m_origin;
    Vector3 m_direction;
};

} // namespace geometry
} // namespace math
} // namespace cpplib
#endif // !__CPPLIB_MATH_GEOMETRY_RAY_H__
