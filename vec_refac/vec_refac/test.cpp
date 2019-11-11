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
	REQUIRE_THROWS_AS(copy.at(1), std::out_of_range);	
}

TEST_CASE("big and small vec", "[vector]") {
	vector<double> big_vec(100);
	for (int i = 0; i < 99; ++i) {
		big_vec.pushback(i + 0.21);
	}
	REQUIRE(big_vec.capacity() == 100);
	big_vec.pushback(3.141592);
	big_vec.pushback(34);
	REQUIRE(big_vec.at(1) == 0.21);
	REQUIRE(big_vec[48] == 48.21);
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
	REQUIRE(small_vec.at(10) == big_vec.at(10));
	REQUIRE(small_vec.size() == big_vec.size());
	reeeel_big_vec.clear();
	REQUIRE(reeeel_big_vec.size() == 0);
	REQUIRE(reeeel_big_vec.capacity() == 10);
	for (unsigned long int i = 0; i < 9999; i++) {
		reeeel_big_vec.pushback(i + 0.21);
	}
	REQUIRE_THROWS_AS(reeeel_big_vec[9999], std::out_of_range);
	//std::cout << reeeel_big_vec[10];
	REQUIRE(reeeel_big_vec[10] == 10.21);
	
	
	


}