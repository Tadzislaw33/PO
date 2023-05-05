#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "LZespolona.hh"

TEST_CASE("test LZespolona Mnozenie") {
    LZespolona x,y,z;
    
    x.re = 1;
    x.im = 1;

    y.re = 0;
    y.im = 2;

	 z = x.operator * (y);
    
    CHECK(z.re == -2);
    CHECK(z.im == 2);
}

