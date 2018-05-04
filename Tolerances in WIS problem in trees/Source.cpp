
#include "Tree.h"
#include "Algorithm.h"
#include <fstream>
#include <chrono>

int main() {
    //performance test
	std::ofstream file("time.dat");
	file << "size time" << std::endl;
	for (int i = 500; i <= 10000; i = i + 500) {
		Tree t(i);
		auto start = std::chrono::system_clock::now();
		computeTolerances(t);
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		file << i << " " << elapsed.count() << std::endl;
	}
    
	Tree t("tree.txt");
	computeTolerances(t);

	return 0;
}

