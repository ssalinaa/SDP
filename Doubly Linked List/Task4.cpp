#include <iostream>

/*
Задача 4

Реализирайте функция removeElements, която по подадена глава
на едносвързан списък и число n премахма всички срещания на числото n в списъка.

Ограничения:

времева сложност: O(n)
пространствена сложност: O(1)

*/

struct Box {

	int value;
	Box* next;

	Box(int value, Box* next) : value(value), next(next) { }
};

void removeElements(Box*& head, int n) {

	if (head == nullptr) {

		return;
	}

	while (head != nullptr && head->value == n) {

		Box* toDelete = head;
		head = head->next;
		delete toDelete;
	}

	Box* current = head;
	Box* previous = nullptr;

	while (current != nullptr) {

		if (current->value == n) {

			if (previous != nullptr) {

				previous->next = current->next;
			}

			Box* toDelete = current;
			current = current->next;
			delete toDelete;
		}
		else {

			previous = current;
			current = current->next;
		}
	}
}

int main() {

	// Creating a test linked list
	Box* node1 = new Box(1, nullptr);
	Box* node2 = new Box(2, nullptr);
	Box* node3 = new Box(3, nullptr);
	Box* node4 = new Box(1, nullptr);
	Box* node5 = new Box(1, nullptr);

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;

	int n = 1;  // The number to remove from the list

	// Removing all occurrences of 'n' from the linked list
	removeElements(node1, n);

	// Printing the modified linked list
	Box* current = node1;
	while (current != nullptr) {

		std::cout << current->value << " ";
		current = current->next;
	}
	std::cout << std::endl;

	// Freeing the memory
	while (node1 != nullptr) {

		Box* toDelete = node1;
		node1 = node1->next;
		delete toDelete;
	}

	return 0;
}