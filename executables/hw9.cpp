//
// Created by 6rayWa1cher on 10.03.2020.
//

#include "../hw9/persons.h"
#include "../hw9/list.h"

int main() {
	std::shared_ptr<Node> list = createList();

	addElement(list, std::make_shared<TGUPerson>("Ivanov", "Petrova 1-23"));

	addElement(list, std::make_shared<TGUPerson>("Petrov", "Ivanova 4-5"));

	printList(list);

	return 0;
}