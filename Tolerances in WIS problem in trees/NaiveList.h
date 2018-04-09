#ifndef NAIVELIST_H
#define NAIVELIST_H

#include <initializer_list>

class NaiveList {
public:
	NaiveList(std::initializer_list<unsigned> a);
	NaiveList();
	~NaiveList();

	void toHead();
	void toLast();
	void toNext();

	void push(unsigned value);
	unsigned getCurrent() const;
	std::size_t getSize() const;

	//NaiveList& operator=(const NaiveList& other);
	NaiveList& operator+=(const NaiveList& other);
private:
	struct Node {
		Node(unsigned value, Node* next);

		unsigned value_;
		Node* next_;
	};
	Node* head_;
	Node* current_;
	Node* last_;

	std::size_t size_;
};

#endif
