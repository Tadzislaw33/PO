#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "LZespolona.hh"

TEST_CASE("test LZespolona Sprzezenie") {
    LZespolona x, y;
    
	 x.re = 1;
     x.im = 1;

	 y = x.Sprzezenie();

    CHECK(y.re == 1);
    CHECK(y.im == -1);
}

