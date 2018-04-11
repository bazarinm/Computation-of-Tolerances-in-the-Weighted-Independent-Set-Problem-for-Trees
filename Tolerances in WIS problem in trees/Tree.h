#ifndef TREE_H
#define TREE_H

#include <vector>
#include <deque>

struct Node {
	std::size_t key;
	double weight;
};

class Tree
{
public:
	Tree(std::size_t root_key, const std::string& filename);
	~Tree() = default;

	std::size_t getSize() const;

	Node getRoot() const;
	Node getNode(std::size_t key) const;
	const std::vector<std::size_t>& getAdjacent(std::size_t key) const;

	void print() const;
private:
	std::size_t size;

	Node root;
	std::vector<Node> nodes;
	std::vector<std::vector<int>> adjacency_matrix;
	std::vector<std::vector<std::size_t>> adjacency_list;
};

#endif