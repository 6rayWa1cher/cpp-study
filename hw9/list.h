//
// Created by 6rayWa1cher on 10.03.2020.
//

#ifndef EDUSANDBOX_LIST_H
#define EDUSANDBOX_LIST_H

#include "persons.h"
#include <memory>

struct Node {
	std::shared_ptr<TGUPerson> data;
	std::shared_ptr<Node> next;
};

struct IntNode {
	int data;
	std::shared_ptr<IntNode> next;
};

// Node

void process(const std::vector<std::reference_wrapper<TGUPerson>>& persons);

void printList(const std::shared_ptr<Node>& head);

std::shared_ptr<Node> createList();

void addElement(const std::shared_ptr<Node>& head, std::shared_ptr<TGUPerson> data);

// IntNode

std::shared_ptr<IntNode> createIntList();

void addElement(const std::shared_ptr<IntNode>& head, int data);

std::ostream& operator<<(std::ostream& stream, const std::shared_ptr<IntNode>& head);

bool listCompare(const std::shared_ptr<IntNode>& head1, const std::shared_ptr<IntNode>& head2);

void swapElements(const std::shared_ptr<IntNode>& prev);

void bubbleSort(const std::shared_ptr<IntNode>& head);

#endif //EDUSANDBOX_LIST_H
