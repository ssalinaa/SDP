#pragma once
#include <iostream>
#include <vector>

template<class T>
class DynamicQueue {

public:
	DynamicQueue() : frontIndex(0), backIndex(0) { }

	const T& front() const {

		if (this->empty()) {

			throw std::out_of_range("Empty queue!");
		}

		return this->queue[this->frontIndex];
	}

	void enqueue(const T& element)
	{
		this->queue.push_back(element);
		this->backIndex = this->queue.size();
	}

	void dequeue() {

		if (this->empty()) {

			throw std::out_of_range("Empty queue!");
		}

		++this->frontIndex;
	}

	bool empty() const {

		return this->frontIndex == this->backIndex;
	}

	void print() const {

		for (size_t i = this->frontIndex; i < this->backIndex; i++) {

			std::cout << this->queue[i] << " ";
		}

		std::cout << std::endl;
	}

private:
	std::vector<T> queue;
	std::size_t frontIndex;
	std::size_t backIndex;
};

int main() {

	try {
		// Create a DynamicQueue of integers
		DynamicQueue<int> myQueue;

		// Enqueue some elements
		myQueue.enqueue(1);
		myQueue.enqueue(3);
		myQueue.enqueue(5);

		// Display the element of the queue
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