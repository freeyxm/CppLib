#include "stdafx.h"
#include <gtest\gtest.h>
#include <Math\Vector3.h>
#include <Math\Matrix4x4.h>
#include <Math\Math.h>
#include <iostream>

using namespace std;
using namespace cpplib::math;

extern void PrintMatrix(const char* name, Matrix4x4& matrix)
{
	cout << name << ":" << endl;
	for (int i = 0; i < 16; ++i)
	{
		cout << matrix[i] << ",";
		if ((i + 1) % 4 == 0)
		{
			cout << endl;
		}
	}
}

TEST(Matrix4x4Test, Scale)
{
}