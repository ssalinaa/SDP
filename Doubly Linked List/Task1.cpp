#include <iostream>
#define CATCH_CONFIG_MAIN

/*

Задача 1
Реализирайте функция removeDuplicatesInSorted, която премахва всички повторения 
на елементи в растящо сортиращ едносвързан списък по подадена глава към списъка.

Ограничения:

времева сложност: O(n)
пространствена сложност: O(1)

*/

struct Box {

	int value;
	Box* next;

	Box(int value, Box* next = nullptr) : value(value), next(next) {}
};

void dellocate(Box* head) {

	if (head == nullptr) {

		return;
	}

	Box* toDelete = head;
	head = head->next;
	delete toDelete;
}

bool areEqual(Box* list1, Box* list2) {

	while (list1 != nullptr && list2 != nullptr) {

		if (list1->value != list2->value) {

			return false;
		}
		list1 = list1->next;
		list2 = list2->next;
	}

	return !list1 && !list2;
}

void removeDuplicates(Box* head) {

	Box* current = head;

	while (current != nullptr && current->next != nullptr) {

		if (current->value == current->next->value) {

			Box* toDelete = current->next;
			current->next = current->next->next;
			delete toDelete;
		}
		else {

			current = current->next;
		}
	}
}

int main() {

	// Creating the first linked list
	Box* list1 = new Box(1);
	list1->next = new Box(2);
	list1->next->next = new Box(2);
	list1->next->next->next = new Box(3);

	std::cout << "Displaying list1: " << std::endl;
	Box* current1 = list1;
	while (current1 != nullptr) {

		std::cout << current1->value << " ";
		current1 = current1->next;
	}
	std::cout << std::endl;

	// Creating the second linked list
	Box* list2 = new Box(1);
	list2->next = new Box(2);
	list2->next->next = new Box(2);
	list2->next->next->next = new Box(3);

	std::cout << "Displaying list2: " << std::endl;
	Box* current2 = list2;
	while (current2 != nullptr) {

		std::cout << current2->value << " ";
		current2 = current2->next;
	}
	std::cout << std::endl;

	// Checking if the two lists are equal
	if (areEqual(list1, list2)) {

		std::cout << "The lists are equal." << std::endl;
	}
	else {

		std::cout << "The lists are not equal." << std::endl;
	}

	// Removing duplicates from the first list
	removeDuplicates(list1);

	// Displaying the result after removing duplicates
	Box* current = list1;
	std::cout << "First list after removing duplicates: ";
	while (current != nullptr) {

		std::cout << current->value << " ";
		current = current->next;
	}
	std::cout << std::endl;

	dellocate(list1);
	dellocate(list2);
}