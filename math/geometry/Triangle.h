#ifndef __CPPLIB_MATH_GEOMETRY_TRIANGLE_H__
#define __CPPLIB_MATH_GEOMETRY_TRIANGLE_H__
#include "../Vector3.h"
#include "Ray.h"

namespace cpplib {
namespace math {
namespace geometry {

class Triangle
{
public:
    Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3);
    ~Triangle();

    void Set(const Vector3& v1, const Vector3& v2, const Vector3& v3);

    bool Raycast(const Ray& ray, float minT, float& t);

    bool GetBarycentricCoords(const Vector3& p, Vector3& res);

    float Area() const;

public:
    Vector3 v1, v2, v3;
};

} // namespace geometry
} // namespace math
} // namespace cpplib
#endif // !__CPPLIB_MATH_GEOMETRY_TRIANGLE_H__
