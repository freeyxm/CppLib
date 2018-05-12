#include "stdafx.h"
#include <gtest\gtest.h>
#include <Math\Vector3.h>
#include <Math\Math.h>
#include <iostream>

using namespace std;
using namespace cpplib::math;

extern void PrintVector3(const char* name, const Vector3& v)
{
	cout << name << " = (" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
}

TEST(Vector3Test, Length)
{
	EXPECT_FLOAT_EQ(Vector3(1, 2, 3).Length(), 3.741657f);
}

TEST(Vector3Test, Distance)
{
	EXPECT_FLOAT_EQ(Vector3::Distance(Vector3::zero, Vector3(9, 8, 7)), 13.928388f);
	EXPECT_FLOAT_EQ(Vector3::Distance(Vector3(1, 2, 3), Vector3(9, 8, 7)), 10.77033f);
}

TEST(Vector3Test, Dot)
{
	EXPECT_FLOAT_EQ(Vector3::Dot(Vector3(1, 2, 3), Vector3::one), 6);
}

TEST(Vector3Test, Cross)
{
	EXPECT_TRUE(Vector3::Cross(Vector3::forward, Vector3::right) == Vector3::up);
	EXPECT_TRUE(Vector3::Cross(Vector3(1, 2, 3), Vector3::one) == Vector3(-1, 2, -1));

	Vector3 vec1(7, 8, 9);
	Vector3 vec2 = Vector3::left;
	Vector3 vec3 = Vector3::Cross(vec1, vec2);
	float angle = acos(Vector3::Dot(vec1, vec3) / (vec1.Length() * vec3.Length()));
	EXPECT_FLOAT_EQ(angle, Math::PI / 2);
}