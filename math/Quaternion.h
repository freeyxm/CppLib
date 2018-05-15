#pragma once
#include "Vector3.h"

namespace cpplib
{
    namespace math
    {
        class Quaternion
        {
        public:
            float x;
            float y;
            float z;
            float w;

        public:
            Quaternion();
            Quaternion(float x, float y, float z, float w);
            Quaternion(const Quaternion& a);

            Quaternion& operator=(const Quaternion& a);
            Quaternion& operator*=(const Quaternion& a);

            Quaternion operator*(const Quaternion& a) const;

            bool operator==(const Quaternion& a) const;
            bool operator!=(const Quaternion& a) const;

            float Magnitude() const;

            Vector3 EulerAngles() const;

            Quaternion Inverse() const;

            static float Dot(const Quaternion& a, const Quaternion& b);

            static Quaternion Euler(const Vector3& euler);

            static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);

        public:
            static const Quaternion identity;
        };
    } // namespace math
} // namespace cpplib
