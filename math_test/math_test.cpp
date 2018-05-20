// math_test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <gtest/gtest.h>

void test_performance();

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    //test_performance();

    int res = RUN_ALL_TESTS();
    getchar();
    return res;
}

