#include "Tree.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

Tree::Tree(std::size_t root_n, const std::string& filename) {
	std::fstream file(filename);
	if (!file.is_open())
		throw "Error opening file";

	std::string char_code;
	std::vector<std::size_t> code;
	std::getline(file, char_code);
	for (char c : char_code)
		code.push_back(c - '0');
	std::reverse(code.begin(), code.end());
	size_ = code.size() + 2;

	nodes_.resize(size_);
	adjacency_list_.resize(size_);
	adjacency_matrix_.resize(size_);
	for (std::vector<int>& row : adjacency_matrix_)
		row.resize(size_);

	std::size_t key;
	int weight;
	while (!file.eof()) {
		file >> key;
		file >> weight;
		nodes_[key] = { key, weight };
		if (key == root_n)
			root_ = nodes_[key];
	}

	std::vector<int> in_code(size_, 0);
	std::vector<int> is_used(size_, 0);
	while (!code.empty()) {
		for (std::size_t i = 0; i < code.size(); ++i)
			if (code[i] < size_)
				in_code[code[i]] = 1;
			else
				throw "Incorrect code!";
		for (std::size_t i = 0; i < size_; ++i)
			if (!in_code[i] && !is_used[i]) {
				adjacency_list_[i].push_back(code.back());
				adjacency_list_[code.back()].push_back(i);

				is_used[i] = 1;
				in_code[code.back()] = 0;
				code.pop_back();
				break;
			}
	}
	for (std::size_t i = 0; i < size_; ++i)
		if (!is_used[i]) {
			adjacency_list_[i].push_back(size_ - 1);
			adjacency_list_[size_ - 1].push_back(i);

			break;
		}

	for (std::size_t i = 0; i < size_; ++i)
		for (std::size_t j = 0; j < adjacency_list_[i].size(); ++j)
			adjacency_matrix_[i][adjacency_list_[i][j]] = 1;
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
	return size_;
}

Node Tree::getRoot() const {
	return root_;
}

Node Tree::getNode(std::size_t key) const {
	return nodes_[key];
}

const std::vector<std::size_t>& Tree::getAdjacent(std::size_t v) const {
	return adjacency_list_[v];
}

void Tree::print() const {
	std::cout << "Root: " << root_.key << std::endl;

	for (std::size_t i = 0; i < adjacency_list_.size(); ++i) {
		std::cout << i << ": ";
		for (std::size_t j = 0; j < adjacency_list_[i].size(); ++j) {
			std::cout << adjacency_list_[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}
