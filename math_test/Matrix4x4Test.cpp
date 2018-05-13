#include "stdafx.h"
#include <gtest\gtest.h>
#include <Math\Vector3.h>
#include <Math\Matrix4x4.h>
#include <Math\Math.h>
#include <iostream>

using namespace std;
using namespace cpplib::math;

extern void PrintMatrix(const char* name, const Matrix4x4& matrix)
{
    cout << name << ":" << endl;
    for (int i = 0; i < 16; ++i)
    {
        cout << matrix[i / 4][i % 4] << ",";
        if ((i + 1) % 4 == 0)
        {
            cout << endl;
        }
    }
}

TEST(Matrix4x4Test, Init)
{
    PrintMatrix("identity", Matrix4x4::identity);
}

TEST(Matrix4x4Test, Translate)
{
    Vector3 vec(1, 2, 3);
    {
        Matrix4x4 matrix = Matrix4x4::Translate(Vector3(2, 3, 4));
        Vector3 res = matrix.MultiplyPoint(vec);
        EXPECT_TRUE(res == Vector3(3, 5, 7));
    }
}

TEST(Matrix4x4Test, Scale)
{
    Vector3 vec(1, 2, 3);
    {
        Matrix4x4 matrix = Matrix4x4::Scale(Vector3(2, 3, 4));
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(2, 6, 12));
    }
    {
        Matrix4x4 matrix2 = Matrix4x4::Scale(Vector3(1, 0, 0), 2);
        Vector3 res = matrix2.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(2, 2, 3));
    }
    {
        Matrix4x4 matrix2 = Matrix4x4::Scale(Vector3(0, 1, 0), 2);
        Vector3 res = matrix2.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(1, 4, 3));
    }
    {
        Matrix4x4 matrix2 = Matrix4x4::Scale(Vector3(0, 0, 1), 2);
        Vector3 res = matrix2.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(1, 2, 6));
    }
    {
        Matrix4x4 matrix2 = Matrix4x4::Scale(Vector3(1, 1, 1), 2);
        Vector3 res = matrix2.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(7, 8, 9));
    }
}

TEST(Matrix4x4Test, Rotate)
{
    Vector3 vec(1, 2, 3);
    {
        Matrix4x4 matrix = Matrix4x4::RotateX(45);
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(1, -0.707107, 3.535534));
    }
    {
        Matrix4x4 matrix = Matrix4x4::RotateY(45);
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(2.828427, 2, 1.414213));
    }
    {
        Matrix4x4 matrix = Matrix4x4::RotateZ(45);
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(-0.7071069, 2.12132, 3));
    }
    {
        Matrix4x4 matrix = Matrix4x4::Rotate(Vector3(10, 20, 30));
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(1.017141, 1.677197, 3.186289));
    }
    {
        Matrix4x4 matrix = Matrix4x4::Rotate(Vector3(1, 0, 0), 45);
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(1, -0.707107, 3.535534));
    }
    {
        Matrix4x4 matrix = Matrix4x4::Rotate(Vector3(3, 2, 1), 45);
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(2.090664, 0.3207744, 3.086459));
    }
}

TEST(Matrix4x4Test, Determinant)
{
    Matrix4x4 matrix = Matrix4x4::Translate(Vector3(7, 8, 9))
        * Matrix4x4::Scale(Vector3(2, 3, 4));
    float res = matrix.Determinant();
    EXPECT_FLOAT_EQ(res, 24);
}

TEST(Matrix4x4Test, Transpose)
{
    Matrix4x4 matrix = Matrix4x4::Scale(Vector3(2, 3, 4));
    Matrix4x4 transpose = matrix.Transpose();
    Matrix4x4 matrix2 = transpose.Transpose();
    EXPECT_EQ(matrix, matrix2);
}

TEST(Matrix4x4Test, Inverse)
{
    Matrix4x4 matrix = Matrix4x4::Translate(Vector3(7, 8, 9))
        * Matrix4x4::Scale(Vector3(2, 3, 4));
    //* Matrix4x4::Rotate(Vector3(5, 6, 7), 45);
    Matrix4x4 inverse = matrix.Inverse();
    Matrix4x4 res = matrix * inverse;
    EXPECT_EQ(res, Matrix4x4::identity);
}