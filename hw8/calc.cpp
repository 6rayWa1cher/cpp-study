//
// Created by 6rayWa1cher on 18.02.2020.
//

#include "calc.h"

#include <utility>
#include <iostream>

double Number::eval() const {
	return num;
}

void Number::print() const {
	std::cout << num;
}

Number::Number(const double num) : num(num) {}

double Number::getNum() const {
	return num;
}

BinaryOperator::BinaryOperator(const std::shared_ptr<Expression>& left, const std::shared_ptr<Expression>& right) :
		left(left), right(right) {

}

double BinaryOperator::eval() const {
	return calculate(left->eval(), right->eval());
}

void
simpleOperatorOutput(const std::shared_ptr<Expression>& left, const std::shared_ptr<Expression>& right, char sign) {
	std::cout << '(';
	left->print();
	std::cout << sign;
	right->print();
	std::cout << ')';
}


void AdditionOperator::print() const {
	simpleOperatorOutput(left, right, '+');
}

double AdditionOperator::calculate(double left, double right) const {
	return left + right;
}

AdditionOperator::AdditionOperator(const std::shared_ptr<Expression>& left, const std::shared_ptr<Expression>& right)
		: BinaryOperator(left, right) {}

void SubtractionOperator::print() const {
	simpleOperatorOutput(left, right, '-');
}

double SubtractionOperator::calculate(double left, double right) const {
	return left - right;
}

SubtractionOperator::SubtractionOperator(const std::shared_ptr<Expression>& left,
                                         const std::shared_ptr<Expression>& right) : BinaryOperator(left, right) {}

MultiplicationOperator::MultiplicationOperator(const std::shared_ptr<Expression>& left,
                                               const std::shared_ptr<Expression>& right) : BinaryOperator(left,
                                                                                                          right) {}

void MultiplicationOperator::print() const {
	simpleOperatorOutput(left, right, '*');
}

double MultiplicationOperator::calculate(double left, double right) const {
	return left * right;
}

DivisionOperator::DivisionOperator(const std::shared_ptr<Expression>& left, const std::shared_ptr<Expression>& right)
		: BinaryOperator(left, right) {}

void DivisionOperator::print() const {
	simpleOperatorOutput(left, right, '/');
}

double DivisionOperator::calculate(double left, double right) const {
	return left / right;
}

NegationOperator::NegationOperator(const std::shared_ptr<Expression>& exp) : UnaryOperator(exp) {

}

void NegationOperator::print() const {
	std::cout << '(' << '-';
	exp->print();
	std::cout << ')';
}

double NegationOperator::calculate(double exp) const {
	return -exp;
}

UnaryOperator::UnaryOperator(const std::shared_ptr<Expression>& exp) : exp(exp) {

}

double UnaryOperator::eval() const {
	return calculate(exp->eval());
}
