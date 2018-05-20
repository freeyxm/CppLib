#ifndef __CPPLIB_MATH_MATH_H__
#define __CPPLIB_MATH_MATH_H__

namespace cpplib {
namespace math {

const float PI = 3.14159265f;
const float Rad2Deg = 180.0f / PI;
const float Deg2Rad = PI / 180.0f;
const float FLOAT_EPSINON = 1E-5f;
const double DOUBLE_EPSINON = 1E-14;

inline bool IsEqual(float a, float b)
{
    float diff = a - b;
    return -FLOAT_EPSINON < diff && diff < +FLOAT_EPSINON;
}

inline bool IsEqual(double a, double b)
{
    double diff = a - b;
    return -DOUBLE_EPSINON < diff && diff < +DOUBLE_EPSINON;
}

} // namespace math
} // namespace cpplib
#endif // !__CPPLIB_MATH_MATH_H__
