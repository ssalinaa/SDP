#pragma once
#include<iostream>

template <class T>
class LinkedStack {

private:
	struct Node {

		T value;
		Node* next;

		Node(const T& value, Node* next = nullptr) : value(value), next(next) { }
	};

	Node* head;

	Node* copy(Node* other) {

		if (!other) {

			return nullptr;
		}

		Node* result = new Node(other->value);
		Node* current = result;

		while (other->next) {

			current->next = new Node(other->next->value);
			current = current->next;
			other = other->next;
		}

		return result;
	}

	void copy(const LinkedStack<T>& other) {

		this->head = copy(other.head);
	}

	void deallocate() {

		while (!this->empty()) {

			this->pop();
		}
	}

public:

	LinkedStack() : head(nullptr) {}

	LinkedStack(const LinkedStack<T>& other)
	{
		this->copy(other);
	}

	LinkedStack& operator = (const LinkedStack<T>& other)
	{
		if (this != &other)
		{
			this->deallocate();
			this->copy(other);
		}

		return *this;
	}

	~LinkedStack()
	{
		this->deallocate();
	}

	const T& top() const {

		if (this->empty()) {

			throw std::out_of_range("Empty stack!");
		}

		return this->head->value;
	}

	void pop() {

		if (this->empty()) {

			throw std::out_of_range("Empty stack!");
		}

		if (!this->head->next) {

			delete this->head;
			this->head = nullptr;
		}
		else {

			Node* toDelete = this->head;
			this->head = this->head->next;
			delete toDelete;
		}
	}

	void push(const T& element) {

		if (this->empty()) {

			this->head = new Node(element);
		}
		else {

			Node* newNode = new Node(element, this->head);
			this->head = newNode;
		}
	}

	bool empty() const {

		return !this->head; 
	}
};

int main() {
	// Create a linked stack of integers
	LinkedStack<int> intStack;

	// Push some elements onto the stack
	intStack.push(10);
	intStack.push(20);
	intStack.push(30);

	// Print the top element of the stack
	try {

		std::cout << "Top element: " << intStack.top() << std::endl;
	}
	catch (const std::out_of_range& e) {

		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "Elements of the stack: " << std::endl;
	while (!intStack.empty()) {

		std::cout << intStack.top() << " ";
		intStack.pop();
	}
	std::cout << std::endl;

	// Check if the stack is empty
	std::cout << "Is the stack empty? " << (intStack.empty() ? "Yes" : "No") << std::endl;

	// Pop the remaining elements
	while (!intStack.empty()) {

		intStack.pop();
	}

	// Try to access the top element of an empty stack
	try {

		std::cout << "Top element: " << intStack.top() << std::endl;
	}
	catch (const std::out_of_range& e) {

		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
