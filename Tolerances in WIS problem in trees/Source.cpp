
#include "Tree.h"
#include "Algorithm.h"
#include "NaiveList.h"
#include <iostream>
#include <list>
#include <algorithm>




int main() {
	std::vector<std::size_t> code = { 1, 2, 2, 3, 0, 1 };
	Tree mytree(0, "tree.txt");
	mytree.print();
	
	TreeTol::alg(mytree);

	std::cin.get();

	return 0;
}