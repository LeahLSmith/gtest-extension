#include <gtest/gtest.h>
#include <math.h>
#include "gtest_ext.h"

double squareRoot(const double a) {
    double b = sqrt(a);
    if(b != b) { // nan check
        return 1.0;
    }else{
        return sqrt(a);
    }
}

double gcd(int n1, int n2)
{
    if (n2 != 0)
       // results in an infinite loop
       // should be computed as gcd(n2, n1 % n2)
       return gcd(n1, n2);
    else 
       return n1;
}

TEST(MathFunctions, SquareRoot) {
    ASSERT_TIMED_BLOCK_START(SquareRootExecutionTime, 1000)
    ASSERT_EQ(6, squareRoot(36.0));
    ASSERT_TIMED_BLOCK_END()
}

TEST(MathFunctions, GCD) {
    ASSERT_TIME(gcd(10, 20), 1000);
    ASSERT_EQ(3, gcd(3, 6));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

