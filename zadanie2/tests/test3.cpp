#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "LZespolona.hh"

TEST_CASE("test LZespolona Roznica") {
    LZespolona x,y,z;
    
    x.re = 1;
    x.im = 1;

    y.re = 1;
    y.im = -3;

	 z = x.operator - (y);
    
    CHECK(z.re == 0);
    CHECK(z.im == 4);
}

