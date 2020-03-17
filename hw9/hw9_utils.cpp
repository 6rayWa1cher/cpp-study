//
// Created by 6rayWa1cher on 10.03.2020.
//

#include <string>
#include "hw9_utils.h"


std::string findAddress(std::shared_ptr<Node> head, const std::string& name) {
	std::shared_ptr<Node> curr = head->next;
	while (curr) {
		std::shared_ptr<TGUPerson> tguPerson = curr->data;
		if (tguPerson && tguPerson->getName() == name) {
			return tguPerson->getAddress();
		}
		curr = curr->next;
	}
	return "";
}
