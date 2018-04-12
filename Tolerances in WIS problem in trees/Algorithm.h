#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Tree.h"
#include <vector>
#include <string>

namespace TreeTol {

	namespace {

		struct InfoNode {
			std::size_t key;
			int weight;

			std::size_t parent_key;
			std::vector<std::size_t> children_keys;

			bool isRoot() const { return key == parent_key; };
			bool isLeaf() const { return children_keys.empty(); };
		};

		std::vector<InfoNode> makeOrdered(Tree& t);
		void printResult(const std::string& filename,
						 const std::vector<double>& l, 
						 const std::vector<double>& u);
	}

	void algorithm(Tree& t);
}

#endif // !ALGORITHM_H
