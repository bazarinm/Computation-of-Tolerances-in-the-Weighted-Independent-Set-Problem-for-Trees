#include "Algorithm.h"

#include <queue>
#include <list>
#include <iostream>

namespace TreeTol {

	namespace {

		void makeOrdered(Tree& t) {
			std::queue<std::size_t> parents;
			std::vector<int> is_used(t.getSize(), 0);

			Node root = t.getRoot();
			BFS_order.emplace_back(root.key, root.weight, root.key);
			parents.push(root.key);
			is_used[root.key] = 1;

			std::size_t count = 0;
			while (!parents.empty()) {
				std::size_t parent_key = parents.front();

				std::vector<std::size_t> adjacent = t.getAdjacent(parent_key);
				for (std::size_t key : adjacent) {
					if (!is_used[key]) {
						parents.push(key);
						BFS_order[count].children_keys.push_back(key);

						Node node = t.getNode(key);
						BFS_order.emplace_back(node.key, node.weight, parent_key);
						is_used[key] = 1;
					}
				}
				parents.pop();
				++count;
			}

		}


	}

	void alg(Tree& t) {
		makeOrdered(t);
		for (InfoNode node : BFS_order) {
			std::cout << "Node " << node.key << ": parent - " << node.parent_key;
			std::cout << " , children: ";
			for (std::size_t ch : node.children_keys)
				std::cout << ch << " ";
			std::cout << std::endl;
		}
		//std::size_t tree_size = t.getSize();

		/*std::vector<std::size_t> w(tree_size);
		std::vector<std::size_t> w_in(tree_size);
		std::vector<std::size_t> w_out(tree_size);

		std::vector<std::list<std::size_t>*> s(tree_size);
		std::vector<std::list<std::size_t>> s_in(tree_size);
		std::vector<std::list<std::size_t>> s_out(tree_size);*/

	}

}
