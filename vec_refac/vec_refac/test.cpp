#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "vector.h"

TEST_CASE("Empty Vector", "[vector]") {
	vector<int> copy(10);
	REQUIRE(copy.size() == 0);
	REQUIRE(copy.capacity() == 10);
	vector<int> temp(copy);
	copy.resize(0);
	REQUIRE(copy.size() == 0);
	REQUIRE(copy.capacity() == 0);
	//REQUIRE_THROWS_AS(copy.at(0), std::out_of_range);























	/*
	temp.pushback(1);
	REQUIRE(temp.size() == 1);
	REQUIRE(temp.capacity() == 10);
	REQUIRE(temp[0] == temp.at(temp.size()));
	REQUIRE(temp[0] == temp.at(0));
	REQUIRE(temp.at(1) == temp.at(temp.size()));
	vector<int> tmp(2);
	tmp.pushback(1);
	temp = tmp;
	*/

	
	
}