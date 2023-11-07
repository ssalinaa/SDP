#include <iostream>
#include <vector>

/*

������������ ������� hasCycle, ����� ��������� ���� � ����������� ������
��� �����. � ���� ������ ��� �����, ��� ���� � ���� ����� ���� �� ���� ���������
������ �� ������ ��� �������������� ��������� �� ������� ���� next ���������.

������:

������ 2

�����������:

������� ��������: O(n)
�������������� ��������: O(n) (�����: O(1))

*/

struct Box {

	int value;
	Box* next;

	Box(int value, Box * next) : value(value), next(next) { }
};

bool contains(std::vector<Box*> dellocatedNodes, Box* node) {

	for (Box* current : dellocatedNodes) {

		if (current == node) {

			return true;
		}
	}

	return false;
}

void dellocateWithCycle(Box* head) {

	std::vector<Box*> dellocatedNodes;

	while (head) {

		if (contains(dellocatedNodes, head)) {

			break;
		}

		Box* current = head;
		head = head->next;

		dellocatedNodes.push_back(current);
		delete current;
	}
}

bool hasCycle(Box* head) {

	if (head->next == nullptr) {

		return false;
	}

	if (head->next == head) {

		return true;
	}

	Box* slow = head;
	Box* fast = head;

	while (fast != nullptr && fast->next != nullptr) {

		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow) {

			return true;
		}
	}

	return false;
}

int main() {

	Box* node1 = new Box{ 1, nullptr };
	Box* node2 = new Box{ 2, nullptr };
	Box* node3 = new Box{ 3, nullptr };

	node1->next = node2;
	node2->next = node3;
	node3->next = node1;

	bool hasCycleResult = hasCycle(node1);

	if (hasCycleResult) {

		std::cout << "The list has cycle." << std::endl;
	}
	else {

		std::cout << "The list does not have cycle." << std::endl;
	}

	dellocateWithCycle(node1);
}