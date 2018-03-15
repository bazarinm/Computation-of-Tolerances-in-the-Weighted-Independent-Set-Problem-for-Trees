
#include "Tree.h"
#include <iostream>
#include <list>
#include <algorithm>

std::vector<std::size_t> maximalIndependentSetSearch(const Tree& tree) {
	std::size_t tree_size = tree.getSize();

	std::vector<std::size_t> w(tree_size);
	std::vector<std::size_t> w_in(tree_size);
	std::vector<std::size_t> w_out(tree_size);

	std::vector<std::list<std::size_t>*> s(tree_size);
	std::vector<std::list<std::size_t>> s_in(tree_size);
	std::vector<std::list<std::size_t>> s_out(tree_size);

	std::vector<Node> BFS_order = tree.getOrdered();
	while (!BFS_order.empty()) {
		Node vertice = BFS_order.back(); BFS_order.pop_back();
		std::size_t vertice_key = vertice.getKey();
		std::size_t vertice_weight = vertice.getWeight();
		if (vertice.isLeaf()) {
			w[vertice_key] = vertice_weight;
			w_in[vertice_key] = vertice_weight;
			w_out[vertice_key] = 0;

			s_in[vertice_key] = { vertice_key };
			s[vertice_key] = &s_in[vertice_key];
			s_out[vertice_key] = { };
		}
		else {
			w_in[vertice_key] = vertice_weight;
			w_out[vertice_key] = 0;

			s_in[vertice_key] = { vertice_key };
			s_out[vertice_key] = { };

			for (std::size_t child_key : vertice.getChildrenKeys()) {
				w_in[vertice_key] += w_out[child_key];
				s_in[vertice_key].splice(s_in[vertice_key].end(), s_in[child_key]);

				w_out[vertice_key] += w[child_key];
				s_out[vertice_key].splice(s_out[vertice_key].end(), *(s[child_key]));
			}

			w[vertice_key] = std::max(w_in[vertice_key], w_out[vertice_key]);
			if (w_in[vertice_key] > w_out[vertice_key]) {
				w[vertice_key] = w_in[vertice_key];
				s[vertice_key] = &s_in[vertice_key]; 
			}
			else {
				w[vertice_key] = w_out[vertice_key];
				s[vertice_key] = &s_out[vertice_key]; 
			}
		}
	}

	return w;
}


int main() {
	std::vector<std::size_t> code = { 1, 2, 2, 3, 0, 1 };
	Tree mytree(0, code);
	mytree.print();

	std::cin.get();

	return 0;
}