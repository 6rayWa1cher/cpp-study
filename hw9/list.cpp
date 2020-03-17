//
// Created by 6rayWa1cher on 10.03.2020.
//

#include <iostream>
#include <utility>
#include <vector>
#include "list.h"

void process(const std::vector<std::reference_wrapper<TGUPerson>>& persons) {
	std::cout << "Inside process :" << std::endl;
	for (auto p : persons) {
		p.get().print();
		std::cout << std::endl;
	}
}

void printList(const std::shared_ptr<Node>& head) {
	for (std::shared_ptr<Node> current = head->next; current != nullptr; current = current->next) {
		current->data->print();
	}
}

std::shared_ptr<Node> createList() {
	return std::make_shared<Node>();
}

void addElement(const std::shared_ptr<Node>& head, std::shared_ptr<TGUPerson> data) {
	std::shared_ptr<Node> newElem = std::make_shared<Node>();
	newElem->next = head->next;
	newElem->data = std::move(data);
	head->next = newElem;
}

std::ostream& operator<<(std::ostream& stream, const std::shared_ptr<IntNode>& head) {
	for (std::shared_ptr<IntNode> current = head->next; current != nullptr; current = current->next) {
		stream << current->data;
	}
	return stream;
}

std::shared_ptr<IntNode> createIntList() {
	return std::make_shared<IntNode>();
}

void addElement(const std::shared_ptr<IntNode>& head, int data) {
	std::shared_ptr<IntNode> newElem = std::make_shared<IntNode>();
	newElem->next = head->next;
	newElem->data = data;
	head->next = newElem;
}

bool listCompare(const std::shared_ptr<IntNode>& head1, const std::shared_ptr<IntNode>& head2) {
	std::shared_ptr<IntNode> curr1 = head1->next, curr2 = head2->next;
	while (curr1 && curr2) {
		if (curr1->data != curr2->data) {
			return false;
		}
		curr1 = curr1->next;
		curr2 = curr2->next;
	}
	return !curr1 && !curr2;
}

void swapElements(const std::shared_ptr<IntNode>& prev) {
	if (!prev) return;
	if (!(prev->next)) return;
	if (!(prev->next->next)) return;
	std::shared_ptr<IntNode> e1 = prev->next, e2 = e1->next;
	prev->next = e2;
	e1->next = e2->next;
	e2->next = e1;
}

void bubbleSort(const std::shared_ptr<IntNode>& head) {
	if (!head) return;
	if (!(head->next)) return;
	if (!(head->next->next)) return;
	std::shared_ptr<IntNode> swapper = head, prev = head->next, next = head->next->next;
	bool changed;
	do {
		changed = false;
		swapper = head, prev = head->next, next = head->next->next;
		while (next) {
			if (prev->data > next->data) {
				swapElements(swapper);
				changed = true;
				prev = swapper->next, next = swapper->next->next;
			}
			swapper = prev, prev = next, next = next->next;
		}
	} while (changed);
}
