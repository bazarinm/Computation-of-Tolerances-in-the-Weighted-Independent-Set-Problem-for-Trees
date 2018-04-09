#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Tree.h"
#include "NaiveList.h"
#include <vector>

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
		std::vector<InfoNode> BFS_order;

		void makeOrdered(Tree& t);
	}
	void alg(Tree& t);
}

#endif // !ALGORITHM_H
