#include "stdafx.h"
#include <gtest\gtest.h>
#include <Math\Vector3.h>
#include <Math\Quaternion.h>
#include <Math\Matrix4x4.h>
#include <Math\Math.h>
#include <iostream>

using namespace std;
using namespace cpplib::math;

TEST(QuaternionTest, Equal)
{
    EXPECT_TRUE(Quaternion(1, 2, 3, 1) == Quaternion(1, 2, 3, 1));
    EXPECT_FALSE(Quaternion(1, 2, 3, 1) == Quaternion(1, 2, 3.1f, 1));
}

TEST(QuaternionTest, Euler)
{
    Vector3 euler(10, 20, 30);
    Quaternion quat = Quaternion::Euler(euler);
    EXPECT_TRUE(quat == Quaternion(0.1276794f, 0.1448781f, 0.2392983f, 0.9515485f));

    Vector3 new_euler = quat.EulerAngles();
    EXPECT_TRUE(euler == new_euler);
}

TEST(QuaternionTest, Matrix)
{
    Vector3 euler(10, 20, 30);
    Quaternion quat = Quaternion::Euler(euler);
    EXPECT_TRUE(quat == Quaternion(0.1276794f, 0.1448781f, 0.2392983f, 0.9515485f));

    Matrix4x4 matrix = Matrix4x4::Rotate(quat);
    Quaternion quat2 = matrix.Rotation();
    EXPECT_TRUE(quat2 == quat);
}

TEST(QuaternionTest, Inverse)
{
    Vector3 euler(10, 20, 30);
    Quaternion quat = Quaternion::Euler(euler);
    Quaternion quat2 = quat.Inverse();
    Quaternion quat3 = quat * quat2;
    EXPECT_TRUE(quat3 == Quaternion(0, 0, 0, 1));

    Quaternion quat4 = quat;
    quat4 *= quat2;
    EXPECT_TRUE(quat4 == quat3);
}

TEST(QuaternionTest, Slerp)
{
    Vector3 euler(10, 20, 30);
    Quaternion quat = Quaternion::Euler(euler);
    Quaternion quat2 = Quaternion::Euler(Vector3(90, 80, 70));
    Quaternion quat3 = Quaternion::Slerp(quat, quat2, 0.5f);
    EXPECT_TRUE(quat3 == Quaternion(0.4442148f, 0.1102437f, 0.09484923f, 0.884038f));
}
