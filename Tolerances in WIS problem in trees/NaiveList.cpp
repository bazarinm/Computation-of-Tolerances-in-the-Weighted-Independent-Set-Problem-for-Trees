#include "NaiveList.h"
#include <initializer_list>

NaiveList::NaiveList(std::initializer_list<unsigned> values) : head_(nullptr),
current_(nullptr), last_(nullptr), size_(0)
{
	for (unsigned value : values)
		push(value);
}

NaiveList::NaiveList() : head_(nullptr),
current_(nullptr), last_(nullptr), size_(0)
{}

NaiveList::Node::Node(unsigned value, Node* next) : value_(value), next_(next)
{}

NaiveList::~NaiveList()
{
	toHead();
	/*for (size_t i = 0; i < size_; ++i) {
		Node* temp = current_;
		toNext();
		delete current_;
	}*/
}

void NaiveList::push(unsigned value) {
	Node* new_node = new Node(value, nullptr);
	if (size_ == 0) {
		last_ = new_node;
		head_ = last_;
		current_ = head_;
	}
	else {
		last_->next_ = new_node;
		last_ = new_node;
	}
	++size_;
}

unsigned NaiveList::getCurrent() const {
	if (current_ == nullptr)
		throw "No elements in the list";

	return current_->value_;
}

std::size_t NaiveList::getSize() const {
	return size_;
}

void NaiveList::toHead() {
	current_ = head_;
}

void NaiveList::toLast() {
	current_ = last_;
}

void NaiveList::toNext() {
	if (current_ != nullptr)
		current_ = current_->next_;
}

//NaiveList& NaiveList::operator=(const NaiveList& other) {
//	head_ = other.head_;
//	current_ = other.current_;
//	last_ = other.last_;
//	return *this;
//}

NaiveList& NaiveList::operator+=(const NaiveList& other) {
	if (other.size_ != 0) {
		if (size_ != 0) {
			last_->next_ = other.head_;
			last_ = other.last_;
			size_ += other.size_;
		}
		else {
			last_ = other.last_;
			head_ = other.head_;
			current_ = other.current_;
			size_ = other.size_;
		}
	}

	return *this;
}