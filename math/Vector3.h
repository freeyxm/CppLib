#pragma once

namespace cpplib
{
    namespace math
    {
        struct Vector3
        {
        public:
            float x, y, z;

        public:
            Vector3();
            Vector3(float x, float y, float z);
            Vector3(const Vector3& a);

            Vector3& operator=(const Vector3& a);
            Vector3& operator+=(const Vector3& a);
            Vector3& operator-=(const Vector3& a);
            Vector3& operator*=(float n);
            Vector3& operator/=(float n);

            Vector3 operator-() const;
            Vector3 operator+(const Vector3& a) const;
            Vector3 operator-(const Vector3& a) const;
            Vector3 operator*(float n) const;
            Vector3 operator/(float n) const;

            bool operator==(const Vector3& a) const;
            bool operator!=(const Vector3& a) const;

            void Zero();
            void Normalize();
            Vector3 normalized() const;

            float Length() const;
            float LengthSquared() const;

            static float Distance(const Vector3& a, const Vector3& b);
            static float DistanceSquared(const Vector3& a, const Vector3& b);

            static Vector3 Cross(const Vector3& a, const Vector3& b);
            static float Dot(const Vector3& a, const Vector3& b);

        public:
            static const Vector3 zero;
            static const Vector3 one;
            static const Vector3 left;
            static const Vector3 right;
            static const Vector3 up;
            static const Vector3 down;
            static const Vector3 forward;
            static const Vector3 back;
            static const Vector3 infinity;
        };
    } // namespace math
} // namespace cpplib
