#include <iostream>
#include <functional>

template<typename T>
class Node {

public:
	T data;
	Node<T> * next;

	Node();
	Node(const T&);
	Node(const T&, Node<T>*);
};

template<typename T>
class LinkedList {

public:
	void copy(const LinkedList& other);
	void cleanup();

	Node<T>* start;
	int size;

	LinkedList();
	LinkedList(Node<T>*, int);
	~LinkedList();
	LinkedList(const LinkedList<T>& other);
	LinkedList& operator=(const LinkedList<T>& other);

	void pushFront(const T&);
	void popFront();
	T head();
	T get(int);
	void pushBack(const T&);
	void popBack();
	T last();
	void insertAt(const T&, int);
	void removeAt(int);

	LinkedList<T> reverse();
	template <typename U>
	LinkedList<U> map(std::function<U(T)>);
	template <typename U>
	LinkedList<T> mergeLists(const LinkedList<U>&, const LinkedList<U> &);
	void print();
};

template<typename T>
Node<T>::Node() : data(data), next(nullptr) { }

template<typename T>
Node<T>::Node(const T & data) : data(data), next(nullptr) { }

template<typename T>
Node<T>::Node(const T& data, Node<T>* next) : data(data), next(next) { }

template<typename T>
LinkedList<T>::LinkedList() : LinkedList<T>(nullptr, 0) { }

template<typename T>
LinkedList<T>::LinkedList(Node<T>* start, int size) : start(start), size(size) { }

template<typename T>
LinkedList<T>::~LinkedList() {

	cleanup();
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) {

	copy(other);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {

	if (this != &other) {

		cleanup();
		copy(other);
	}

	return *this;
}

template<typename T>
void LinkedList<T>::copy(const LinkedList<T>& other) {

	if (other.start == nullptr) {

		this->start = nullptr;
		return;
	}

	Node<T>* newStart = new Node<T>(other.start->data);
	this->start = newStart;

	Node<T>* currentOther = other.start->next;
	Node<T>* previous = newStart;

	while (currentOther != nullptr) {

		Node<T>* newNode = new Node<T>(currentOther->data);
		previous->next = newNode;
		previous = newNode;
		currentOther = currentOther->next;
	}
	this->size = other.size;
}

template<typename T>
void LinkedList<T>::cleanup() {

	if (start == nullptr) {

		return;
	}

	Node<T>* current = start;
	Node<T>* child = current->next;
	while (current != nullptr) {

		delete current;
		current = child;
		while (child != nullptr) {

			child = child->next;
		}
	}
}

template<typename T>
void LinkedList<T>::pushFront(const T& element) {

	Node<T>* newNode = new Node<T>(element, start);
	start = newNode;
	size++;
}

template<typename T>
void LinkedList<T>::popFront() {

	Node<T>* temp = start;
	start = start->next;
	size--;
	delete temp;
	
}

template<typename T>
T LinkedList<T>::head() {

	if (start == nullptr) {

		return T();
	}

	return start->data;
}

template<typename T>
T LinkedList<T>::get(int index) {

	if (index < 0 || index >= size) {

		return T();
	}

	Node<T>* current = start;
	int i = 0;
	while (i < index) {

		current = current->next;
		i++;
	}
	return current->data;
}

template<typename T>
void LinkedList<T>::pushBack(const T& element) {

	Node<T>* newNode = new Node<T>(element);

	if (start == nullptr) {

		start = newNode;
	}
	else {

		Node<T>* current = start;
		while (current->next != nullptr) {

			current = current->next;
		}
		current->next = newNode;
	}
	size++;
}

template<typename T>
void LinkedList<T>::popBack() {

	if (start == nullptr) {

		return;
	}

	if (start->next == nullptr) {

		delete start;
		start = nullptr;
	} 
	else {

		Node<T>* current = start;
		Node<T>* previous = nullptr;

		while (current->next != nullptr) {

			previous = current;
			current = current->next;
		}
		previous->next = nullptr;
		delete current;
	}
	size--;
}

template<typename T>
T LinkedList<T>::last() {

	if (start == nullptr) {

		return T();
	}

	Node<T>* current = start;
	while (current->next != nullptr) {

		current = current->next;
	}

	return current->data;
}

template<typename T>
void LinkedList<T>::insertAt(const T& element, int index) {

	if (index < 0 || index > size) {

		return;
	}
	if (index == 0) {

		pushFront(element);
		return;
	}
	Node<T>* current = start;
	int i = 0;
	while (i < index - 1) {

		current = current->next;
		i++;
	}
	Node<T>* newNode = new Node<T>(element, current->next);
	current->next = newNode;
	size++;	
}

template<typename T>
void LinkedList<T>::removeAt(int index) {

	if (index < 0 || index >= size) {

		return;
	}
	if (index == 0) {

		popFront();
		return;
	}

	Node<T>* current = start;
	int i = 0;
	while (i < index - 1) {

		current = current->next;
		i++;
	}

	Node<T>* nodeToDelete = current->next;
	current->next = current->next->next;
	delete nodeToDelete;
	size--;
}

template <typename T>
LinkedList<T> LinkedList<T>::reverse() {

	if (start == nullptr) {

		return LinkedList<T>();
	}

	Node<T>* current = start->next;
	Node<T>* reversedCurrent = new Node<T>(start->data);

	while (current != nullptr) {

		Node<T>* newNode = new Node<T>(current->data, reversedCurrent);
		reversedCurrent = newNode;
		current = current->next;
	}

	return LinkedList<T>(reversedCurrent, size);
}

template<typename T>
template<typename U>
LinkedList<U> LinkedList<T>::map(std::function<U(T)> f) {

	if (start == nullptr) {

		return LinkedList<U>();
	}

	Node<T>* current = start->next;
	Node<U>* newStart = new Node<U>(f(start->data));
	Node<U>* resultCurrent = newStart;

	while (current != nullptr) {

		Node<U>* newNode = new Node<U>(f(current->data));
		resultCurrent->next = newNode;
		resultCurrent = newNode;
		current = current->next;
	}
	return LinkedList<U>(newStart, size);
}

template<typename T>
LinkedList<T> mergeLists(const LinkedList<T>& first, const LinkedList<T>& second) {

	if (first.start == nullptr) {

		return second;
	}

	if (second.start == nullptr) {

		return first;
	}

	Node<T>* currentFirst;
	Node<T>* currentSecond;
	Node<T>* newStart;
	Node<T>* resultCurrent;

	if (first.start->data > second.start->data) {

		currentFirst = first.start;
		currentSecond = second.start->next;
		newStart = new Node<T>(second.start->data);
		resultCurrent = newStart;
	}
	else {

		currentFirst = first.start->next;
		currentSecond = second.start;
		newStart = new Node<T>(first.start->data);
		resultCurrent = newStart;
	}

	while (currentFirst != nullptr && currentSecond != nullptr)
	{
		if (currentFirst->data > currentSecond->data)
		{
			Node<T>* newNode = new Node<T>(currentSecond->data);
			resultCurrent->next = newNode;
			resultCurrent = newNode;
			currentSecond = currentSecond->next;
		}
		else
		{
			Node<T>* newNode = new Node<T>(currentFirst->data);
			resultCurrent->next = newNode;
			resultCurrent = newNode;
			currentFirst = currentFirst->next;
		}
	}

	Node<T>* remaining;
	if (currentFirst == nullptr) {

		remaining = currentSecond;
	}
	else {

		remaining = currentFirst;
	}

	while (remaining != nullptr)
	{
		Node<T>* newNode = new Node<T>(remaining->data);
		resultCurrent->next = newNode;
		resultCurrent = newNode;
		remaining = remaining->next;
	}

	return LinkedList<T>(newStart, first.size + second.size);
}

template<typename T>
void LinkedList<T>::print() {

	Node<T>* current = start;
	while (current != nullptr) {

		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << std::endl;
}

int main() {

	LinkedList<int> list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);

	std::cout << "Original List: ";
	list.print();

	LinkedList<int> reversedList = list.reverse();
	std::cout << "Reversed List: ";
	reversedList.print();

	std::cout << "First Element: " << list.head() << std::endl;
	std::cout << "Last Element: " << list.last() << std::endl;

	list.insertAt(99, 2);
	std::cout << "List after inserting 99 at index 2: ";
	list.print();

	list.removeAt(1);
	std::cout << "List after removing element at index 1: ";
	list.print();

	list.popFront();
	std::cout << "List after popping front: ";
	list.print();

	list.popBack();
	std::cout << "List after popping back: ";
	list.print();


	LinkedList<int> mappedList = list.map<int>([](int x) { return x * 2; });
	std::cout << "Mapped List: ";
	mappedList.print();

	LinkedList<int> list1;
	list1.pushBack(1);
	list1.pushBack(4);
	list1.pushBack(6);
	std::cout << "List 1: ";
	list1.print();

	LinkedList<int> list2;
	list2.pushBack(2);
	list2.pushBack(3);
	list2.pushBack(5);
	std::cout << "List 2: ";
	list2.print();

	LinkedList<int> mergedList = mergeLists(list1, list2);
	std::cout << "Merged List: ";
	mergedList.print();



	return 0;
}