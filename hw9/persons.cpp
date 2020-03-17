// ConsoleApplication4.cpp: определяет точку входа для консольного приложения.
//
#include <iostream>
#include "persons.h"
#include <memory>
#include <utility>

TGUPerson::TGUPerson(std::string name, std::string address)
		: _name(std::move(name)),
		  _address(std::move(address)) {}

void TGUPerson::setAddress(const std::string& address) {
	_address = address;
}

void TGUPerson::print() const {
	std::cout << _name << " adress: " << _address;
}

std::string TGUPerson::getAddress() {
	return this->_address;
}

std::string TGUPerson::getName() {
	return this->_name;
}

TGUStudent::TGUStudent(const std::string& name, const std::string& address, int course, double rating)
		: TGUPerson(name, address),
		  _course(course),
		  _rating(rating) {
}

void TGUStudent::setRating(double newRating) {
	_rating = newRating;
}

void TGUStudent::print() const {
	TGUPerson::print();
	std::cout << " course: " << _course << " rating: " << _rating;
}