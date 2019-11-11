#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include "vector.h"

void test(int);
void test2(int);
/*
int main() {
	for (int i = 10; i < 100000; i *= 10) {
		test(i);
	}
	std::cout << "fertig\n";
}
*/

void test(int number) {
	vector <int> Vektor(0);

	auto t1 = std::chrono::steady_clock::now(); //Aktueller Zeitpunkt wird gespeichert

	for (int i = number; i > 0; i--) {
		Vektor.pushback(i);
	}

	auto t2 = std::chrono::steady_clock::now();// Zeitpunkt nach Ausführung von push_back wird gespeichert
	auto d_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();//Zeitspanne wird in Microsekunden ermittelt

	//Vektor.~vector();

	std::ofstream data;
	std::string name = "data_25.csv";

	data.open(name, std::ofstream::app);
	data << number << ";" << d_nano / number << ";" << "\n";
	data.close();

}

void test2(int number) {
	std::vector<int> vec;
	auto t1 = std::chrono::steady_clock::now(); //Aktueller Zeitpunkt wird gespeichert

	for (int i = number; i > 0; i--) {
		vec.push_back(i);
	}

	auto t2 = std::chrono::steady_clock::now();// Zeitpunkt nach Ausführung von push_back wird gespeichert
	auto d_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();//Zeitspanne wird in Microsekunden ermittelt
	
	std::ofstream data;
	std::string name = "data_vec.csv";

	data.open(name, std::ofstream::app);
	data << number << ";" << d_nano / number << ";" << "0" << "\n";
	data.close();
	
}