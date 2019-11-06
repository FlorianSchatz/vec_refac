#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "vector.h"

TEST_CASE("Erster Beispieltest", "[vector]") {

	vector<int> temp();
	REQUIRE( temp.size() == 0);
}