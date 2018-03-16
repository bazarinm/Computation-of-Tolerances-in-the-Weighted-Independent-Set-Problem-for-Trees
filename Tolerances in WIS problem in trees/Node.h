#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <vector>

class Node 
{
public:
	Node(std::size_t key, std::size_t weight);
	bool isLeaf() const;
	bool isRoot() const;

	std::size_t getKey() const;
	void setKey(std::size_t k);
	std::size_t getWeight() const;
	void setWeight(std::size_t w);

	std::size_t getParentKey() const;
	void setParentKey(std::size_t p);
	const std::vector<std::size_t>& getChildrenKeys() const;
	void setChilrenKeys(const std::vector<std::size_t>& c);
private:
	std::size_t key_;
	std::size_t weight_;

	std::size_t parent_key_;
	std::vector<std::size_t> children_keys_;
};

#endif