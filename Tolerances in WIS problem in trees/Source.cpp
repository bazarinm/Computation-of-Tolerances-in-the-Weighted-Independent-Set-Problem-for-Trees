
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

	//NaiveList a({ 1, 2, 3, 4 });
	//NaiveList b({ 5, 6, 7 });
	//NaiveList c({ 8, 9, 10 });
	//NaiveList o({});
	//a += b;
	//b += a;
	//a.toHead();
	//for (int i = 0; i < a.getSize(); ++i) {
	//	std::cout << a.getCurrent();
	//	a.toNext();
	//}
	//std::cin.get();

	return 0;
}