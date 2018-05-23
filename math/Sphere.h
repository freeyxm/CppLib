#ifndef __CPPLIB_MATH_GEOMETRY_SPHERE_H__
#define __CPPLIB_MATH_GEOMETRY_SPHERE_H__
#include "Vector3.h"
#include "Ray.h"

namespace cpplib {
namespace math {
namespace geometry {

class Sphere
{
public:
    Sphere(Vector3 center, float radius);
    ~Sphere();

    void Set(Vector3 center, float radius);

    bool Raycast(const Ray& ray, float& t);

private:
    Vector3 m_center;
    float m_radius;
};

} // namespace geometry
} // namespace math
} // namespace cpplib
#endif // !__CPPLIB_MATH_GEOMETRY_SPHERE_H__
