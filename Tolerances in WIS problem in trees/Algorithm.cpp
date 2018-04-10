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
		std::size_t size = t.getSize();
		std::size_t root = t.getRoot().key;

		std::vector<double> w(size);
		std::vector<double> win(size);
		std::vector<double> wout(size);

		std::vector<std::size_t> s;

		std::vector<double> Win(size);
		std::vector<double> Wout(size);

		std::vector<double> l(size);
		std::vector<double> u(size);

		for (std::size_t i = 0; i < size; ++i) {
			InfoNode x = BFS_order[size - i - 1]; //reverse BFS order
			if (x.isLeaf()) {
				win[x.key] = x.weight;
				wout[x.key] = 0;

				w[x.key] = win[x.key];
			}
			else {
				win[x.key] = x.weight;
				wout[x.key] = 0;

				for (std::size_t y : x.children_keys) {
					win[x.key] += wout[y];
					wout[x.key] += w[y];	
				}

				w[x.key] = std::max(win[x.key], wout[x.key]);
			}
		}

		std::vector<int> is_used(size, 0);
		for (InfoNode x : BFS_order) {
			if (x.isRoot()) {
				Win[x.key] = win[x.key];
				Wout[x.key] = wout[x.key];
			}
			else {
				Win[x.key] = Wout[x.parent_key] - w[x.key] + win[x.key];
				Wout[x.key] = wout[x.key] + std::max(Win[x.parent_key] - wout[x.key],
													 Wout[x.parent_key] - w[x.key]);
			}
			if (!is_used[x.parent_key] && win[x.key] >= wout[x.key]) {
				s.push_back(x.key);
				is_used[x.key] = 1;
			}
		}

		for (InfoNode x : BFS_order) {
			if (is_used[x.key]) {
				l[x.key] = w[root] - Wout[x.key];
				u[x.key] = -1;
			}
			else {
				u[x.key] = w[root] - Win[x.key];
				l[x.key] = -1;
			}
		}


		std::cout << "max independed set: " << std::endl;
		for (std::size_t key : s) {
			std::cout << "key " << key << " of weight " << t.getNode(key).weight << std::endl;
		}
		std::cout << "total weight = " << w[t.getRoot().key];

		std::cout << std::endl << std::endl;

		std::cout << "tolerances: " << std::endl;
		for (InfoNode x : BFS_order) {
			std::size_t key = x.key;
			if(is_used[key])
				std::cout << "key " << key << " with lower tolerance " << l[key] << std::endl;
			else
				std::cout << "key " << key << " with upper tolerance " << u[key] << std::endl;
		}
	}

}
