#include <iostream>

template<typename T>
class Node {

public:
	T data;
	Node<T>* previous;
	Node<T>* next;

	Node();
	Node(const T& data);
	Node(const T& data, Node<T>* next, Node<T>* previous);
};

template<typename T>
class DoublyLinkedList {

public:
	Node<T> *start;
	Node<T> *end;

	void copy(const DoublyLinkedList<T>&);
	void cleanup();
	void remove(Node<T>* node);

	DoublyLinkedList();
	~DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList& other);
	DoublyLinkedList& operator=(const DoublyLinkedList& other);

	void pushFront(const T& element);
	void popFront();
	void pushBack(const T& element);
	void popBack();
	T head();
	T last();

	void print();
	void reverse();
	void removeDuplicates();
};

template <typename T>
Node<T>::Node() : data(), next(nullptr), previous(nullptr) {}

template <typename T>
Node<T>::Node(const T& data) : Node(data, nullptr, nullptr) {}

template <typename T>
Node<T>::Node(const T& data, Node<T>* next, Node<T>* previous) : data(data), next(next), previous(previous) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : start(nullptr), end(nullptr) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	cleanup();
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : start(nullptr), end(nullptr)
{
	copy(other);
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)
{
	if (this != &other)
	{
		cleanup();
		copy(other);
	}

	return *this;
}

template <typename T>
void DoublyLinkedList<T>::copy(const DoublyLinkedList<T>& other)
{
	if (other.start == nullptr) {

		return;
	}

	Node<T>* current = other.start;
	while (current != other.end) {

		pushBack(current->data);
		current = current->next;
	}
	pushBack(current->data);
}

template <typename T>
void DoublyLinkedList<T>::cleanup() {

	if (start == nullptr) {

		return;
	}

	Node<T>* current = start;
	while (current != end) {

		Node<T>* toRemove = current;
		current = current->next;
		delete toRemove;
	}
	delete current;
}

template <typename T>
void DoublyLinkedList<T>::remove(Node<T>* node) {

	if (node == start) {

		popFront();
		return;
	}

	if (node == end) {

		popBack();
		return;
	}

	Node<T>* nodeBefore = node->previous;
	Node<T>* nodeAfter = node->next;
	nodeBefore->next = nodeAfter;
	nodeAfter->previous = nodeBefore;

	delete node;
}

template<typename T>
void DoublyLinkedList<T>::pushFront(const T& element) {

	Node<T>* newNode = new Node<T>(element);

	if (start = nullptr) {

		start = newNode;
		end = newNode;
	}
	else {

		newNode->next = start;
		start->previous = newNode;
		start = newNode;	
	}
}

template<typename T>
void DoublyLinkedList<T>::popFront() {

	if (start == nullptr && end == nullptr) {

		return;
	}

	if (start == end) {

		delete start;
		start = nullptr;
		end = nullptr;
		return;
	}

	Node<T>* toRemove = start;
	start = start->next;
	start->previous = nullptr;
	delete toRemove;
}

template<typename T>
void DoublyLinkedList<T>::pushBack(const T& element) {

	Node<T>* newNode = new Node<T>(element);

	if (start == nullptr) {

		start = newNode;
		end = newNode;
	}
	else {

		end->next = newNode;
		newNode->previous = end;
		end = newNode;
	}
}

template<typename T>
void DoublyLinkedList<T>::popBack() {

	if (start == nullptr && end == nullptr) {

		return;
	}

	if (start == end) {

		delete start;
		start = nullptr;
		end == nullptr;
		return;
	}

	Node<T>* toRemove = end;
	end = end->previous;
	end->next = nullptr;

	delete toRemove;
}

template <typename T>
T DoublyLinkedList<T>::head() {

	if (start == nullptr) {

		throw std::out_of_range("The list is empty!");
	}
	return start->data;
}

template <typename T>
T DoublyLinkedList<T>::last() {

	if (end == nullptr) {

		throw std::out_of_range("The list is empty!");
	}
	return end->data;
}

template <typename T>
void DoublyLinkedList<T>::print() {

	if (start == nullptr) {

		return;
	}

	Node<T>* current = start;
	while (current != end) {

		std::cout << current->data << " ";
		current = current->next;
	}

	std::cout << current->data << " ";
}

template <typename T>
void DoublyLinkedList<T>::reverse() {

	if (start == nullptr || start == end) {

		return;
	}

	Node<T>* current = start;

	while (current != nullptr) {

		Node<T>* temp = current->next;
		current->next = current->previous;
		current->previous = temp;

		current = temp;
	}

	Node<T>* temp = start;
	start = end;
	end = temp;
}

template <typename T>
void DoublyLinkedList<T>::removeDuplicates() {

	Node<T>* current = start;

	while (current != nullptr) {

		Node<T>* rest = current->next;
		while (rest != nullptr) {

			Node<T>* next = rest->next;
			if (rest->data == current->data) {

				remove(rest);
			}
			rest = next;
		}
		current = current->next;
	}
}

int main() {

	DoublyLinkedList<int> list;

	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(2);
	list.pushBack(3);
	list.pushBack(4);
	list.pushBack(4);
	list.pushBack(5);

	std::cout << "Original List: ";
	list.print();
	std::cout << std::endl;

	list.reverse();
	std::cout << "Reversed List: ";
	list.print();
	std::cout << std::endl;

	list.removeDuplicates();
	std::cout << "List with Duplicates Removed: ";
	list.print();
	std::cout << std::endl;

	list.popFront();
	list.popBack();
	std::cout << "List after popping front and back: ";
	list.print();
	std::cout << std::endl;

	std::cout << "First Element: " << list.head() << std::endl;
	std::cout << "Last Element: " << list.last() << std::endl;

	return 0;
}
