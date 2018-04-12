
#include "Tree.h"
#include "Algorithm.h"
#include <iostream>
#include <fstream>
#include <chrono>

int main() {
	//std::ofstream file("time.dat");
	//file << "size time" << std::endl;
	//for (int i = 500; i <= 10000; i = i + 500) {
	//	Tree t(i);
	//	auto start = std::chrono::system_clock::now();
	//	TreeTol::algorithm(t);
	//	auto end = std::chrono::system_clock::now();
	//	std::chrono::duration<double> elapsed = end - start;
	//	file << i << " " << elapsed.count() << std::endl;
	//}
	Tree t(476);
	TreeTol::algorithm(t);

	return 0;
}

