#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <vector>
#include <deque>

class Tree
{
public:
	Tree(size_t root, std::vector<std::size_t>& code);
	~Tree();

	std::size_t getSize() const;

	const std::vector<std::size_t>& getAdjacent(std::size_t v) const;
	const std::vector<Node>& getOrdered() const;
	const Node& getFromOrdered(std::size_t v) const;

	void print() const;
private:
	std::size_t size;
	std::vector<std::vector<std::size_t>> adjacency_list;
	std::vector<Node> ordered_list;

	void toOrdered(std::size_t v);
};

#endif