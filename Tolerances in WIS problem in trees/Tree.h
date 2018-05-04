#ifndef TREE_H
#define TREE_H

#include <vector>

struct Node {
	std::size_t key;
	double weight;
};

class Tree
{
public:
	Tree(const std::string& filename);
	Tree(std::size_t size);
	~Tree() = default;

	std::size_t getSize() const;

	Node getNode(std::size_t key) const;
	const std::vector<std::size_t>& getAdjacent(std::size_t key) const;

	void print() const;
private:
	std::size_t _size;

	std::vector<Node> _nodes;
	std::vector<std::vector<std::size_t>> _adjacency_list;
};

#endif