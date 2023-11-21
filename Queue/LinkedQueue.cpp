#pragma once
#include <iostream>

template<class T>
class LinkedQueue {
	
private:
	struct Node {

		T value;
		Node* next;
		Node* previous;

		Node(const T& value, Node* next, Node* previous) :
			value(value), next(next), previous(previous) { }
	};

	Node* frontNode;
	Node* backNode;

	void deallocate() {

		while (!this->empty()) {

			this->dequeue();
		}
	}

	void copy(const LinkedQueue<T>& other) {

		Node* current = other.frontNode;

		while (current != nullptr) {

			this->enqueue(current->value);
			current = current->next;
		}
	}

public:
	LinkedQueue() : frontNode(nullptr), backNode(nullptr) { }

	LinkedQueue(const LinkedQueue<T>& other) {

		this->copy(other);
	}

	LinkedQueue& operator = (const LinkedQueue<T>& other)
	{
		if (this != &other)
		{
			this->deallocate();
			this->copy(other);
		}

		return *this;
	}

	~LinkedQueue() {

		this->deallocate();
	}
	
	const T& front() const {

		if (this->empty()) {

			throw std::out_of_range("Empty queue!");
		}

		return this->frontNode->value;
	}

	void dequeue() {

		if (this->empty()) {

			throw std::out_of_range("Empty queue!");
		}

		Node* toDelete = this->frontNode;
		this->frontNode = this->frontNode->next;
		if (this->frontNode != nullptr) {

			this->frontNode->previous = nullptr;
		}
		delete toDelete;
	}

	void enqueue(const T& element) {

		Node* newNode = new Node(element, nullptr, this->backNode);
		if (this->empty()) {

			this->frontNode = newNode;
		}
		else {

			this->backNode->next = newNode;
		}
		this->backNode = newNode;
	}

	bool empty() const {

		return this->frontNode == nullptr;
	}

	void print() const {

		Node* current = this->frontNode;

		while (current != nullptr) {

			std::cout << current->value << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}
};

int main() {

	try {
		// Create a LinkedQueue of integers
		LinkedQueue<int> myQueue;

		// Enqueue some elements
		myQueue.enqueue(1);
		myQueue.enqueue(3);
		myQueue.enqueue(5);

		// Display elements of the queue
		std::cout << "The elements of the queue are: " << std::endl;
		myQueue.print();

		// Display the front element
		std::cout << "Front element: " << myQueue.front() << std::endl;

		// Dequeue an element
		myQueue.dequeue();

		// Display the front element after dequeue
		std::cout << "Front element after dequeue: " << myQueue.front() << std::endl;

		// Check if the queue is empty
		if (myQueue.empty()) {

			std::cout << "Queue is empty." << std::endl;
		}
		else {

			std::cout << "Queue is not empty." << std::endl;
		}

		// Dequeue the remaining elements
		myQueue.dequeue();
		myQueue.dequeue();

		// Attempting to dequeue from an empty queue should throw an exception
		myQueue.dequeue(); // This should throw an exception

	}
	catch (const std::exception& e) {

		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
