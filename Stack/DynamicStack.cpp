#pragma once
#include <iostream>
#include <vector>

template <class T>
class DynamicStack {

	public:
	std::vector<T> stack;

	const T& top()  const {

		if (this->empty()) {

			throw std::out_of_range("Empty stack!");
		}

		return this->stack.back();
	}

	void push(const T& element) {

		this->stack.push_back(element);
	}

	void pop() {

		if (this->empty()) {

			throw std::out_of_range("Empty stack!");
		}
		this->stack.pop_back();
	}

	bool empty() const {

		return this->stack.empty();
	}
};

int main() {

	DynamicStack<int> stack;
	stack.push(10);
	stack.push(20);
	stack.push(30);
	stack.push(40);
	stack.push(50);

	try {

		std::cout << "Top element: " << stack.top() << std::endl;
	}
	catch (const std::out_of_range& e) {

		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "Elements of the stack: " << std::endl;
	while (!stack.empty()) {

		std::cout << stack.top() << " ";
		stack.pop();
	}
	std::cout << std::endl;

	try {

		stack.pop();
	}
	catch (std::out_of_range& e) {

		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "Is the stack empty? " << (stack.empty() ? "Yes" : "No") << std::endl;

	while (!stack.empty()) {

		stack.pop();
	}

	try {
		std::cout << "Top element: " << stack.top() << std::endl;
	}
	catch (std::out_of_range& e) {

		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}