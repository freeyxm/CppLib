#pragma once
#include "Vector3.h"

namespace cpplib
{
    namespace math
    {
        struct Matrix4x4
        {
        public:
            union
            {
                float m[4][4];
                struct
                {
                    float m11, m12, m13, m14;
                    float m21, m22, m23, m24;
                    float m31, m32, m33, m34;
                    float m41, m42, m43, m44;
                };
            };

        public:
            Matrix4x4();
            Matrix4x4(const Matrix4x4& t);
            Matrix4x4(float const (&t)[16]);
            Matrix4x4(
                float m11, float m12, float m13, float m14,
                float m21, float m22, float m23, float m24,
                float m31, float m32, float m33, float m34,
                float m41, float m42, float m43, float m44
            );

            float* operator[](int row);
            const float* operator[](int row) const;

            bool operator==(const Matrix4x4& t) const;
            bool operator!=(const Matrix4x4& t) const;

            Matrix4x4& operator=(const Matrix4x4& t);
            Matrix4x4& operator*=(const Matrix4x4& t);

            Matrix4x4 operator*(const Matrix4x4& t) const;

            Vector3 MultiplyVector(const Vector3& v) const;
            Vector3 MultiplyPoint(const Vector3& v) const;

            static Matrix4x4 Translate(const Vector3& v);

            static Matrix4x4 Scale(const Vector3& scale);
            static Matrix4x4 Scale(const Vector3& axis, float k);

            static Matrix4x4 Rotate(const Vector3& axis, float angle);
            static Matrix4x4 Rotate(const Vector3& euler);
            static Matrix4x4 RotateX(float angle);
            static Matrix4x4 RotateY(float angle);
            static Matrix4x4 RotateZ(float angle);

            static Matrix4x4 TRS(const Vector3& t, const Vector3& r, const Vector3& s);

        public:
            float Determinant() const;
            Matrix4x4 Inverse() const;
            Matrix4x4 Transpose() const;

        private:
            const int N = 4;
            void SwapRow(int r1, int r2);
            void AddRow(int r1, int r2, float k);

        public:
            const static Matrix4x4 identity;
            const static Matrix4x4 zero;
        };

        Vector3 operator*(const Vector3& v, const Matrix4x4& t);
        Vector3 operator*(const Matrix4x4& t, const Vector3& v);

    } // namespace math
} // namespace cpplib
