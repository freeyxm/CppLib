#include "stdafx.h"
#include <iostream>
#include <math/Matrix4x4.h>
#include <utility/Timer.h>

using namespace std;
using namespace cpplib::math;
using namespace cpplib::utility;

void test_performance()
{
    Timer timer;
    float sum = 0;
    int count = 2000000000;

    timer.Start();
    for (int i = 0; i < count; ++i)
    {
        volatile Matrix4x4 matrix = Matrix4x4::Rotate(Vector3(10, 20, 30));
        sum += matrix.m11;
    }
    timer.Stop();

    cout << "time: " << timer.Milliseconds() << endl;
}
