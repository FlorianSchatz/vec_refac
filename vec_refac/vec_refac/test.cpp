#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "vector.h"

TEST_CASE("Erster Beispieltest", "[vector]") {
	vector<int> copy(10);
	REQUIRE(copy.size() == 10);
	REQUIRE(copy.capacity() == 10);
	vector<int> temp(copy);
	REQUIRE(temp.size() == 10);
	REQUIRE(temp.capacity() == 10);
	REQUIRE(temp[11] == NULL);
	REQUIRE(temp.at(11) == 0);
	vector<int> tmp(2);
	tmp.pushback(1);
	temp = tmp;

	
}