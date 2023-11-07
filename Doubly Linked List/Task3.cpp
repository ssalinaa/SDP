#include <iostream>

/*
Задача 3

Реализирайте функция getIntersectionNode, която при дадени глави на два 
едносвързани списъка връща кутията, при която двата списъка се пресичат.
Ако двата списъка не се пресичат, върнете nullptr.

Ограничения:

времева сложност: O(n)
пространствена сложност: O(1)

*/

struct Box {

	int value;
	Box* next;

	Box(int value, Box* next) : value(value), next(next) { }
};

int getSize(Box* list) {

	int size = 0;
	while (list != nullptr) {

		list = list->next;
		size++;
	}

	return size;
}

Box* getIntersectionNode(Box* head1, Box* head2) {

	int size1 = getSize(head1);
	int size2 = getSize(head2);

	Box* minList = head1;
	Box* maxList = head2;

	if (size1 > size2) {

		std::swap(minList, maxList);
	}

	std::size_t difference = std::abs(size1 - size2);

	for (size_t i = 0; i < difference; i++)
	{
		maxList = maxList->next;
	}

	while (minList != nullptr && maxList != nullptr) {

		if (minList == maxList) {

			return minList;
		}

		minList = minList->next;
		maxList = maxList->next;
	}

	return nullptr;
}

int main() {

	// Creating two test linked lists
	Box* nodeA1 = new Box{ 1, nullptr };
	Box* nodeA2 = new Box{ 2, nullptr };
	Box* nodeA3 = new Box{ 3, nullptr };

	nodeA1->next = nodeA2;
	nodeA2->next = nodeA3;

	Box* nodeB1 = new Box{ 7, nullptr };
	Box* nodeB2 = new Box{ 8, nullptr };

	nodeB1->next = nodeB2;
	nodeB2->next = nodeA2; // This is where the lists intersect

	// Finding the intersecting node
	Box* intersectionNode = getIntersectionNode(nodeA1, nodeB1);

	if (intersectionNode != nullptr) {
		std::cout << "The intersecting node has a value of: " << intersectionNode->value << std::endl;
	}
	else {
		std::cout << "The lists do not intersect." << std::endl;
	}

	// Freeing the memory
	delete nodeA1;
	delete nodeA2;
	delete nodeA3;
	delete nodeB1;
	delete nodeB2;
}
