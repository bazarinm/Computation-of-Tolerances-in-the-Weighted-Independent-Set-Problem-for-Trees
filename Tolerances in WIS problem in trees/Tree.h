#ifndef TREE_H
#define TREE_H

#include <vector>
#include <deque>

struct Node {
	std::size_t key;
	int weight;
};

class Tree
{
public:
	Tree(std::size_t root, const std::string& filename);
	~Tree();

	std::size_t getSize() const;

	Node getRoot() const;
	Node getNode(std::size_t key) const;
	const std::vector<std::size_t>& getAdjacent(std::size_t v) const;

	void print() const;
private:
	std::size_t size;

	Node root;
	std::vector<Node> nodes;
	std::vector<std::vector<std::size_t>> adjacency_list;
	std::vector<std::vector<int>> adjacency_matrix;
};

#endif