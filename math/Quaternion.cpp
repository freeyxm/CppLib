#include "stdafx.h"
#include "Quaternion.h"
#include "Matrix4x4.h"
#include "Math.h"
#include <cmath>

namespace cpplib
{
    namespace math
    {
        const Quaternion Quaternion::identity(0, 0, 0, 1);

        Quaternion::Quaternion()
            : x(0), y(0), z(0), w(0)
        {
        }

        Quaternion::Quaternion(float x, float y, float z, float w)
            : x(x), y(y), z(z), w(w)
        {
        }

        Quaternion::Quaternion(const Quaternion & a)
            : x(a.x), y(a.y), z(a.z), w(a.w)
        {
        }

        void Quaternion::Set(float x, float y, float z, float w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        Quaternion & Quaternion::operator=(const Quaternion & a)
        {
            this->x = a.x;
            this->y = a.y;
            this->z = a.z;
            this->w = a.w;
            return *this;
        }

        Quaternion & Quaternion::operator*=(const Quaternion & a)
        {
            float _x = w * a.x + x * a.w + z * a.y - y * a.z;
            float _y = w * a.y + y * a.w + x * a.z - z * a.x;
            float _z = w * a.z + z * a.w + y * a.x - x * a.y;
            float _w = w * a.w - x * a.x - y * a.y - z * a.z;
            this->x = _x;
            this->y = _y;
            this->z = _z;
            this->w = _w;
            return *this;
        }

        Quaternion Quaternion::operator*(const Quaternion & a) const
        {
            float _x = w * a.x + x * a.w + z * a.y - y * a.z;
            float _y = w * a.y + y * a.w + x * a.z - z * a.x;
            float _z = w * a.z + z * a.w + y * a.x - x * a.y;
            float _w = w * a.w - x * a.x - y * a.y - z * a.z;
            return Quaternion(_x, _y, _z, _w);
        }

        Vector3 Quaternion::operator*(const Vector3 & a) const
        {
            return Matrix4x4::Rotate(*this) * a;
        }

        bool Quaternion::operator==(const Quaternion & a) const
        {
            return Math::IsEqual(x, a.x) && Math::IsEqual(y, a.y) && Math::IsEqual(z, a.z) && Math::IsEqual(w, a.w);
        }

        bool Quaternion::operator!=(const Quaternion & a) const
        {
            return !Math::IsEqual(x, a.x) || !Math::IsEqual(y, a.y) || !Math::IsEqual(z, a.z) || !Math::IsEqual(w, a.w);
        }

        float Quaternion::Magnitude() const
        {
            return sqrt(x * x + y * y + z * z + w * w);
        }

        Vector3 Quaternion::EulerAngles() const
        {
            float h, p, b;
            float sp = -2 * (y * z - w * x);
            // ¼ì²éÍòÏòËø
            if (fabs(sp) > 0.9999f)
            {
                p = Math::PI * 0.5f * sp;
                h = atan2(-x * z + w * y, 0.5f - y * y - z * z);
                b = 0.0f;
            }
            else
            {
                p = asin(sp);
                h = atan2(x * z + w * y, 0.5f - x * x - y * y);
                b = atan2(x * y + w * z, 0.5f - x * x - z * z);
            }
            p *= Math::Rad2Deg;
            h *= Math::Rad2Deg;
            b *= Math::Rad2Deg;
            return Vector3(p, h, b);
        }

        Quaternion Quaternion::Inverse() const
        {
            float m = -1.0f / Magnitude();
            return Quaternion(x*m, y*m, z*m, w);
        }

        float Quaternion::Dot(const Quaternion & a, const Quaternion & b)
        {
            return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
        }

        Quaternion Quaternion::Euler(const Vector3 & euler)
        {
            float p = euler.x * Math::Deg2Rad * 0.5f;
            float h = euler.y * Math::Deg2Rad * 0.5f;
            float b = euler.z * Math::Deg2Rad * 0.5f;
            float cp = cos(p);
            float sp = sin(p);
            float ch = cos(h);
            float sh = sin(h);
            float cb = cos(b);
            float sb = sin(b);
            float ch_sp = ch * sp;
            float ch_cp = ch * cp;
            float sh_cp = sh * cp;
            float sh_sp = sh * sp;

            return Quaternion(
                ch_sp * cb + sh_cp * sb,
                sh_cp * cb - ch_sp * sb,
                ch_cp * sb - sh_sp * cb,
                ch_cp * cb + sh_sp * sb
            );
        }

        Quaternion Quaternion::Slerp(const Quaternion & a, const Quaternion & b, float t)
        {
            bool opposite = false;
            float cosA = Dot(a, b);
            if (cosA < 0)
            {
                cosA = -cosA;
                opposite = true;
            }
            float k0, k1;
            if (cosA > 0.9999f)
            {
                k0 = 1 - t;
                k1 = t;
            }
            else
            {
                float sinA = sqrt(1 - cosA * cosA);
                float omega = atan2(sinA, cosA);
                float oneOverSinA = 1.0f / sinA;
                k0 = sin((1 - t) * omega) * oneOverSinA;
                k1 = sin(t * omega) * oneOverSinA;
            }
            if (opposite)
            {
                k1 = -k1;
            }
            return Quaternion(
                a.x*k0 + b.x*k1,
                a.y*k0 + b.y*k1,
                a.z*k0 + b.z*k1,
                a.w*k0 + b.w*k1
            );
        }

    } // namespace math
} // namespace cpplib
