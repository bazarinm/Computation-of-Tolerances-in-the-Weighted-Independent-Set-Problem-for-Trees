
#include "Node.h"

#include <cstddef>
#include <vector>

bool Node::isLeaf() const {
	return children_keys.empty();
}

bool Node::isRoot() const {
	return parent_key == key;
}

std::size_t Node::getKey() const {
	return key;
}

void Node::setKey(std::size_t k) {
	key = k;
}

std::size_t Node::getWeight() const {
	return weight;
}

void Node::setWeight(std::size_t w) {
	weight = w;
}

std::size_t Node::getParentKey() const {
	return parent_key;
}

void Node::setParentKey(std::size_t p) {
	parent_key = p;
}

const std::vector<std::size_t>& Node::getChildrenKeys() const {
	return children_keys;
}

void Node::setChilrenKeys(const std::vector<std::size_t>& c) {
	children_keys = c;
}