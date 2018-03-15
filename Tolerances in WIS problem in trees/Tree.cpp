#include "Tree.h"

#include <vector>
#include <deque>
#include <queue>
#include <iostream>

Tree::Tree(std::size_t root, std::vector<size_t>& code)
{
	std::reverse(code.begin(), code.end());

	size = code.size() + 2;
	adjacency_list.resize(size);

	std::vector<int> in_code(size, 0);
	std::vector<int> is_used(size, 0);

	while (!code.empty()) {
		for (std::size_t i = 0; i < code.size(); ++i)
			if (code[i] < size)
				in_code[code[i]] = 1;
			else
				throw "Incorrect code!";

		for (std::size_t i = 0; i < size; ++i)
			if (!in_code[i] && !is_used[i]) {
				adjacency_list[i].push_back(code.back());
				adjacency_list[code.back()].push_back(i);

				is_used[i] = 1;
				in_code[code.back()] = 0;
				code.pop_back();
				break;
			}
	}
	for (std::size_t i = 0; i < size; ++i)
		if (!is_used[i]) {
			adjacency_list[i].push_back(size - 1);
			adjacency_list[size - 1].push_back(i);

			break;
		}

	toOrdered(root);
}

void Tree::toOrdered(std::size_t v) {
	std::queue<std::size_t> parents;
	std::vector<int> is_used(size, 0);
	parents.push(v);

	Node n;
	n.setKey(v);
	n.setParentKey(v);
	ordered_list.push_back(n);
	is_used[v] = 1;

	while (!parents.empty()) {
		v = parents.front();

		for (std::size_t i = 0; i < adjacency_list[v].size(); ++i) {
			if (!is_used[adjacency_list[v][i]]) {
				parents.push(adjacency_list[v][i]);

				//Node n;
				n.setKey(adjacency_list[v][i]);
				n.setParentKey(v);
				n.setChilrenKeys(adjacency_list[i]);

				ordered_list.push_back(n);
				is_used[adjacency_list[v][i]] = 1;
			}
		}
		parents.pop();
	}
}

Tree::~Tree()
{
}


std::size_t Tree::getSize() const {
	return size;
}

const std::vector<std::size_t>& Tree::getAdjacent(std::size_t v) const {
	return adjacency_list[v];
}

const std::vector<Node>& Tree::getOrdered() const {
	return ordered_list;
}

const Node& Tree::getFromOrdered(std::size_t v) const {
	return ordered_list[v];
}


void Tree::print() const {
	for (std::size_t i = 0; i < adjacency_list.size(); ++i) {
		std::cout << i << ": ";
		for (std::size_t j = 0; j < adjacency_list[i].size(); ++j) {
			std::cout << adjacency_list[i][j] << ", ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	for (std::size_t i = 0; i < ordered_list.size(); ++i) {
		std::cout << ordered_list[i].getKey() << ", ";
	}
}
