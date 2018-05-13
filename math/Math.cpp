#include "stdafx.h"
#include "Math.h"

namespace cpplib
{
    namespace math
    {
        const float Math::PI = 3.14159f;
        const float Math::Rad2Deg = 180.0f / Math::PI;
        const float Math::Deg2Rad = Math::PI / 180.0f;

        bool Math::IsEqual(float a, float b)
        {
            float diff = a - b;
            return -1E-5f < diff && diff < +1E-5f;
        }

        bool Math::IsEqual(double a, double b)
        {
            double diff = a - b;
            return -1E-14 < diff && diff < +1E-14;
        }
    } // namespace math
} // namespace cpplib