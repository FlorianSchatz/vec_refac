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
	REQUIRE_THROWS_AS(copy.at(0), std::out_of_range);


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

TEST_CASE("big and small vec", "[vector]") {
	vector<double> big_vec(100);
	for (int i = 0; i < 99; ++i) {
		big_vec.pushback(i + 0.21);
	}
	REQUIRE(big_vec.capacity() == 100);
	big_vec.pushback(3.141592);
	big_vec.pushback(34);
	REQUIRE(big_vec.at(50) == 49.21);
	REQUIRE(big_vec[49] == 49.21);
	REQUIRE(big_vec.capacity() == unsigned long int(100 * 1.3));
	big_vec.resize(50);
	REQUIRE(big_vec.capacity()== 50);
	REQUIRE(big_vec.size() == 50);
	vector<double> reeeel_big_vec(big_vec);
	REQUIRE(reeeel_big_vec.size() == big_vec.size());
	REQUIRE(reeeel_big_vec.at(17) == big_vec.at(17));
	vector<double> small_vec(10);
	reeeel_big_vec = small_vec;
	REQUIRE(reeeel_big_vec.size() == small_vec.size());
	small_vec = big_vec;
	REQUIRE(small_vec.at(17) == big_vec.at(17));
	REQUIRE(small_vec.size() == big_vec.size());
	reeeel_big_vec.clear();
	REQUIRE(reeeel_big_vec.size() == 0);
	REQUIRE(reeeel_big_vec.capacity() == 10);
	for (unsigned long int i = 0; i < 999; ++i) {
		big_vec.pushback(i + 0.21);
	}
	REQUIRE_THROWS_AS(reeeel_big_vec[999], std::out_of_range);
	REQUIRE(reeeel_big_vec[998] == 998.21);
	

	


}