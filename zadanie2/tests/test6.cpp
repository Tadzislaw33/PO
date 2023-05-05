#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "LZespolona.hh"
#include "WyrazenieZesp.hh"
using namespace std;



TEST_CASE("Lzespolona - wczytywanie "){

	LZespolona x;
	istringstream in("(2+3i)");
	in >> x;
	ostringstream out;
	out << x;
	CHECK("(2+3i)" == out.str());
}

TEST_CASE("test LZespolona operator równości") {

	LZespolona x, y;
	bool result, result1;

    x.re = 1;
    x.im = 1;

    y.re = 1;
    y.im = 1;


	 result = ((x.re == y.re) && (x.im == y.im));
	 result1 = (x == y);

	 CHECK( result == result1 );

}
