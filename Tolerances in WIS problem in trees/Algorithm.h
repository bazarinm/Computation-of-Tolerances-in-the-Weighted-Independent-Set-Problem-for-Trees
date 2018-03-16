#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Tree.h"
#include <vector>

namespace TreeTol {
	namespace {
		struct InfoNode {
			std::size_t key;
			int weight;

			std::size_t parent_key;
			std::vector<std::size_t> children_keys;
		};
		std::vector<InfoNode> BFS_order;

		void makeOrdered(Tree& t);
	}
	void alg(Tree& t);
}

#endif // !ALGORITHM_H
