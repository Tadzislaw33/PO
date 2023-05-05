#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "LZespolona.hh"

TEST_CASE("test LZespolona Dzielenie") {
    LZespolona x,y,z;
    
    x.re = 1;
    x.im = 1;

    y.re = 2;
    y.im = 2;

	 z = x / y;

    CHECK(z.re == 0.5);
    CHECK(z.im == 0);
}

TEST_CASE("test LZespolona Dzielenie przez zero") {
    LZespolona x,y;
    
    x.re = 1.;
    x.im = 1.;

    y.re = 0.;
    y.im = 0.;
    
    CHECK_THROWS(x/y);
}

