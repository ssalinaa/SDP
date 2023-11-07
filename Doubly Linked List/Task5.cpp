#include <iostream>

/*
Задача 5

Реализирайте функция reverseList, която по подедена глава на едносвързан списък обръща списъка.

Ограничения:

времева сложност: O(n)
пространствена сложност: O(1)

*/

struct Box {

	int value;
	Box* next;

	Box(int value, Box* next) : value(value), next(next) { }
};

void reverseList(Box*& head) {

	Box* temp = nullptr;
	Box* previous = nullptr;
	Box* current = head;

	while (current != nullptr) {

		temp = current->next;
		current->next = previous;
		previous = current;
		current = temp;
	}
	
	head = previous;
}

int main() {

    // Creating a test linked list
    Box* node1 = new Box(1, nullptr);
    Box* node2 = new Box(2, nullptr);
    Box* node3 = new Box(3, nullptr);
    Box* node4 = new Box(4, nullptr);

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;

    std::cout << "Original Linked List: " << std::endl;

    Box* current = node1;
    while (current != nullptr) {

        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;

    // Reversing the linked list
    reverseList(node1);

    std::cout << "Reversed Linked List: " << std::endl;

    current = node4;
    while (current != nullptr) {

        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;

    // Freeing the memory
    while (node4 != nullptr) {

        Box* toDelete = node4;
        node4 = node4->next;
        delete toDelete;
    }
}
