#include "Tree.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

Tree::Tree(std::size_t root_, const std::string& filename) {
	std::fstream file(filename);
	if (!file.is_open())
		throw "Error opening file";

	std::string char_code;
	std::vector<std::size_t> code;
	std::getline(file, char_code);
	for (char c : char_code)
		code.push_back(c - '0');
	std::reverse(code.begin(), code.end());
	size = code.size() + 2;

	nodes.resize(size);
	adjacency_list.resize(size);
	adjacency_matrix.resize(size);
	for (std::vector<int>& row : adjacency_matrix)
		row.resize(size);

	std::size_t key;
	int weight;
	while (!file.eof()) {
		file >> key;
		file >> weight;
		nodes[key] = { key, weight };
		if (key == root_)
			root = nodes[key];
	}

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

	for (std::size_t i = 0; i < size; ++i)
		for (std::size_t j = 0; j < adjacency_list[i].size(); ++j)
			adjacency_matrix[i][adjacency_list[i][j]] = 1;
}

//void Tree::toOrdered(std::size_t v) {
//	std::queue<std::size_t> parents;
//	std::vector<int> is_used(size, 0);
//	parents.push(v);
//
//	Node n;
//	n.setKey(v);
//	n.setParentKey(v);
//	ordered_list.push_back(n);
//	is_used[v] = 1;
//
//	while (!parents.empty()) {
//		v = parents.front();
//
//		for (std::size_t i = 0; i < adjacency_list[v].size(); ++i) {
//			if (!is_used[adjacency_list[v][i]]) {
//				parents.push(adjacency_list[v][i]);
//
//				//Node n;
//				n.setKey(adjacency_list[v][i]);
//				n.setParentKey(v);
//				n.setChilrenKeys(adjacency_list[i]);
//
//				ordered_list.push_back(n);
//				is_used[adjacency_list[v][i]] = 1;
//			}
//		}
//		parents.pop();
//	}
//}

Tree::~Tree()
{
}


std::size_t Tree::getSize() const {
	return size;
}

Node Tree::getRoot() const {
	return root;
}

Node Tree::getNode(std::size_t key) const {
	return nodes[key];
}

const std::vector<std::size_t>& Tree::getAdjacent(std::size_t v) const {
	return adjacency_list[v];
}

void Tree::print() const {
	std::cout << "Root: " << root.key << std::endl;

	for (std::size_t i = 0; i < adjacency_list.size(); ++i) {
		std::cout << i << ": ";
		for (std::size_t j = 0; j < adjacency_list[i].size(); ++j) {
			std::cout << adjacency_list[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}
