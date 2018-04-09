#include "Algorithm.h"

#include "Tree.h"
#include "NaiveList.h"
#include <queue>
#include <list>
#include <iostream>

namespace TreeTol {

	namespace {

		void makeOrdered(Tree& t) {
			std::queue<std::size_t> parents;
			std::vector<int> is_used(t.getSize(), 0);

			Node root = t.getRoot();
			InfoNode info_root = { root.key, root.weight, root.key };
			BFS_order.push_back(info_root);
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
						InfoNode info_node = { node.key, node.weight, parent_key };
						BFS_order.push_back(info_node);
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
		std::size_t size = BFS_order.size();

		std::vector<std::size_t> w(size);
		std::vector<std::size_t> win(size);
		std::vector<std::size_t> wout(size);

		std::vector<NaiveList*> s(size);
		std::vector<NaiveList> sin(size);
		std::vector<NaiveList> sout(size);
		std::vector<NaiveList> sin_aux(size);
		std::vector<NaiveList> sout_aux(size);

		std::vector<std::size_t> Win(size);
		std::vector<std::size_t> Wout(size);

		for (std::size_t i = 0; i < size; ++i) {
			InfoNode x = BFS_order[size - i - 1]; //reverse BFS order
			if (x.isLeaf()) {
				sin[x.key] = { x.key };
				sin_aux[x.key] = { x.key };
				win[x.key] = x.weight;
				sout[x.key] = {};
				sout_aux[x.key] = {};
				wout[x.key] = 0;

				w[x.key] = win[x.key];
				s[x.key] = &sin[x.key];
			}
			else {
				sin[x.key] = { x.key };
				sin_aux[x.key] = { x.key };
				win[x.key] = x.weight;
				sout[x.key] = {};
				sout_aux[x.key] = {};
				wout[x.key] = 0;

				for (std::size_t y : x.children_keys) {
					sin[x.key] += sout[y];
					sin_aux[x.key] += sout[y];
					win[x.key] += wout[y];
					sout[x.key] += *s[y];
					wout[x.key] += w[y];	
				}

				w[x.key] = std::max(win[x.key], wout[x.key]);
				if (win[x.key] > wout[x.key]) s[x.key] = &sin_aux[x.key];
				else s[x.key] = &sout[x.key];
			}
		}

		std::cout << "max independed set: " << std::endl;
		NaiveList MWIS = *s[t.getRoot().key];
		unsigned key;
		for (std::size_t i = 0; i < MWIS.getSize(); ++i) {
			key = MWIS.getCurrent();
			MWIS.toNext();
			std::cout << "key " << key << " of weight " << t.getNode(key).weight << std::endl;
		}
		std::cout << "total weight = " << w[t.getRoot().key];
	}

}
