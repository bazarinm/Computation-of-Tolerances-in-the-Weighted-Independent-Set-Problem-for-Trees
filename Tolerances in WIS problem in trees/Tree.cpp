#include "Tree.h"

#include <vector>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>

Tree::Tree(std::size_t root_key, const std::string& filename) {
	std::fstream file(filename);
	if (!file.is_open())
		throw std::exception("Cant open file");

	std::string code_string;
	std::vector<std::size_t> code;
	std::getline(file, code_string);
	for (char c : code_string)
		code.push_back(c - '0');
	std::reverse(code.begin(), code.end());
	size = code.size() + 2;

	nodes.resize(size);
	adjacency_list.resize(size);
	adjacency_matrix.resize(size);
	for (std::vector<int>& row : adjacency_matrix)
		row.resize(size);

	std::size_t key;
	double weight;
	while (!file.eof()) {
		file >> key;
		file >> weight;
		nodes[key] = { key, weight };
		if (key == root_key)
			root = nodes[key];
	}

	std::vector<int> in_code(size, 0);
	std::vector<int> is_used(size, 0);

	for (std::size_t code_key : code)
		if (code_key > size)
			throw std::exception("Bad code");
		else
			++in_code[code_key];

	while (!code.empty()) {


		for (std::size_t i = 0; i < size; ++i)
			if (in_code[i] == 0 && !is_used[i]) {
				std::size_t code_key = code.back();

				adjacency_list[i].push_back(code_key);
				adjacency_list[code_key].push_back(i);

				adjacency_matrix[i][code_key] =
					adjacency_matrix[code_key][i] = 1;

				is_used[i] = 1;
				--in_code[code_key];
				code.pop_back();
				break;
			}
	}
	for (std::size_t i = 0; i < size; ++i)
		if (!is_used[i]) {
			adjacency_list[i].push_back(size - 1);
			adjacency_list[size - 1].push_back(i);

			adjacency_matrix[i][size - 1] =
				adjacency_matrix[size - 1][i] = 1;

			break;
		}

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

const std::vector<std::size_t>& Tree::getAdjacent(std::size_t key) const {
	return adjacency_list[key];
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
