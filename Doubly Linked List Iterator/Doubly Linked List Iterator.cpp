#include <iostream>

template<typename T>
class Node {

public:
	T data;
	Node<T>* previous;
	Node<T>* next;

	Node();
	Node(const T& data);
	Node(const T& data, Node<T>* previous, Node<T>* next);
};

template<typename T, typename ReturnT>
class DoublyLinkedListIterator {

private:
	Node<T>* current;
	Node<T>* last;

public:
	DoublyLinkedListIterator();
	DoublyLinkedListIterator(Node<T>*);
	DoublyLinkedListIterator(Node<T>*, Node<T>*);

	ReturnT operator*();
	DoublyLinkedListIterator<T, ReturnT>& operator++();
	DoublyLinkedListIterator<T, ReturnT>& operator--();
	bool operator !=(const DoublyLinkedListIterator<T, ReturnT>&);

	template<typename C>
	friend class DoublyLinkedList;
};

template<typename T, typename ReturnT>
DoublyLinkedListIterator<T, ReturnT>::DoublyLinkedListIterator() : current(nullptr), last(nullptr) { }

template<typename T, typename ReturnT>
DoublyLinkedListIterator<T, ReturnT>::DoublyLinkedListIterator(Node<T>* current) : current(current), last(nullptr) { }

template<typename T, typename ReturnT>
DoublyLinkedListIterator<T, ReturnT>::DoublyLinkedListIterator(Node<T>* current, Node<T> *last) : current(current), last(last) { }

template<typename T, typename ReturnT>
ReturnT DoublyLinkedListIterator<T, ReturnT>::operator*() {

	return current->data;
}

template<typename T, typename ReturnT>
DoublyLinkedListIterator<T, ReturnT> &DoublyLinkedListIterator<T, ReturnT>::operator++() {

	current = current->next;
	return *this;
}

template<typename T, typename ReturnT>
DoublyLinkedListIterator<T, ReturnT>& DoublyLinkedListIterator<T, ReturnT>::operator--() {

	if (current == nullptr) {

		current = last;
	}
	else {

		current = current->previous;
	}

	return *this;
}

template<typename T, typename ReturnT>
bool DoublyLinkedListIterator<T, ReturnT>::operator!=(const DoublyLinkedListIterator<T, ReturnT> &other) {

	return current != other.current;
}

template<typename T>
class DoublyLinkedList {

private:
	Node<T>* start;
	Node<T>* _end;

	void copy(const DoublyLinkedList<T>&);
	void cleanup();
	void remove(Node<T> *);

public:
	DoublyLinkedListIterator<T, T> begin() const;
	DoublyLinkedListIterator<T, T> end() const;
	
	DoublyLinkedListIterator<T, T&> begin();
	DoublyLinkedListIterator<T, T&> end();

	DoublyLinkedList();
	~DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList<T>&);
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
	void pushFront(const T&);
	void popFront();
	void pushBack(const T&);
	void popBack();
	T head();
	T last();
	void print();
	void reverse();
	void removeDuplicates();
	bool isEmpty();

	template <typename ReturnT>
	void deleteElement(DoublyLinkedListIterator<T, ReturnT>);
};

template <typename T>
DoublyLinkedListIterator<T, T> DoublyLinkedList<T>::begin() const
{
	return DoublyLinkedListIterator<T, T>(start);
}

template <typename T>
DoublyLinkedListIterator<T, T> DoublyLinkedList<T>::end() const
{
	return DoublyLinkedListIterator<T, T>(nullptr, _end);
}

template <typename T>
DoublyLinkedListIterator<T, T&> DoublyLinkedList<T>::begin()
{
	return DoublyLinkedListIterator<T, T&>(start);
}

template <typename T>
DoublyLinkedListIterator<T, T&> DoublyLinkedList<T>::end() 
{
	return DoublyLinkedListIterator<T, T&>(nullptr, _end);
}

template <typename T>
Node<T>::Node() : data(), next(nullptr), previous(nullptr) {}

template <typename T>
Node<T>::Node(const T& data) : Node(data, nullptr, nullptr) {}

template <typename T>
Node<T>::Node(const T& data, Node<T>* next, Node<T>* previous) : data(data), next(next), previous(previous) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : start(nullptr), _end(nullptr) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	cleanup();
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : start(nullptr), _end(nullptr)
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

template<typename T>
void DoublyLinkedList<T>::copy(const DoublyLinkedList& other) {

	if (other.start == nullptr) {

		return;
	}

	Node<T>* current = other.start;
	while (current != other._end) {

		pushBack(current->data);
		current = current->next;
	}
	pushBack(current->data);
	
}

template<typename T>
void DoublyLinkedList<T>::cleanup() {

	if (start == nullptr) {

		return;
	}

	Node<T>* current = start;
	while (current != _end) {

		Node<T>* toRemove = current;
		current = current->next;
		delete toRemove;
	}

	delete current;
}

template<typename T>
void DoublyLinkedList<T>::remove(Node<T>* node) {

	if (node == start) {

		popFront();
		return;
	}
	if (node == _end) {

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
void DoublyLinkedList<T>::pushFront(const T& data) {

	Node<T>* newNode = new Node<T>(data);

	if (start == nullptr) {

		start = newNode;
		_end = newNode;
	}
	else {

		newNode->next = start;
		start->previous = newNode;
		start = newNode;
	}
}

template<typename T>
void DoublyLinkedList<T>::print() {

	if (start == nullptr) {

		return;
	}

	Node<T>* current = start;
	while (current != _end) {

		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << current->data << " ";
}

template<typename T>
void DoublyLinkedList<T>::popFront() {

	if (start == nullptr && _end == nullptr) {

		return;
	}
	if (start == _end) {

		delete start;
		start = nullptr;
		_end = nullptr;

		return;
	}

	Node<T>* toRemove = start;
	start = start->next;
	start->previous = nullptr;

	delete toRemove;
}

template<typename T>
void DoublyLinkedList<T>::popBack() {

	if (start == nullptr && _end == nullptr) {

		return;
	}

	if (start == _end) {

		delete start;
		start == nullptr;
		_end = nullptr;

		return;
	}

	Node<T>* toRemove = _end;
	_end = _end->previous;
	_end->next = nullptr;

	delete toRemove;
}

template<typename T>
T DoublyLinkedList<T>::head() {

	if (start == nullptr) {

		throw std::out_of_range("The list is empty.");
	}

	return start->data;
}

template<typename T>
T DoublyLinkedList<T>::last() {

	if (_end == nullptr) {

		throw std::out_of_range("The list is empty.");
	}

	return _end->data;
}

template<typename T>
void DoublyLinkedList<T>::pushBack(const T& data) {

	Node<T>* newNode = new Node<T>(data);

	if (start == nullptr)
	{
		start = newNode;
		_end = newNode;
	}
	else {

		_end->next = newNode;
		newNode->previous = _end;
		_end = newNode;
	}
}

template<typename T>
void DoublyLinkedList<T>::reverse() {

	if (start == nullptr || start == _end) {

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
	start = _end;
	_end = temp;
}

template<typename T>
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

template<typename T>
bool DoublyLinkedList<T>::isEmpty() {

	return start == nullptr;
}

template <typename T>
template <typename ReturnT>
void DoublyLinkedList<T>::deleteElement(DoublyLinkedListIterator<T, ReturnT> iterator)
{
	remove(iterator.current);
}

int main() {
	DoublyLinkedList<int> myList;

	myList.pushBack(1);
	myList.pushBack(2);
	myList.pushBack(3);
	myList.pushBack(2);
	myList.pushBack(4);
	myList.pushBack(5);

	std::cout << "Original List: ";
	myList.print();
	std::cout << std::endl;

	myList.reverse();
	std::cout << "Reversed List: ";
	myList.print();
	std::cout << std::endl;

	myList.removeDuplicates();
	std::cout << "List after removing duplicates: ";
	myList.print();
	std::cout << std::endl;

	DoublyLinkedListIterator<int, int&> it = myList.begin();
	while (it != myList.end()) {
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;

	DoublyLinkedListIterator<int, int&> elementToDelete = myList.begin();
	++elementToDelete; 
	myList.deleteElement(elementToDelete);
	std::cout << "List after deleting an element: ";
	myList.print();
	std::cout << std::endl;

	return 0;
}

