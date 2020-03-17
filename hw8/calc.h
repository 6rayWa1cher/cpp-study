//
// Created by 6rayWa1cher on 18.02.2020.
//

#ifndef EDUSANDBOX_CALC_H
#define EDUSANDBOX_CALC_H

#include <memory>

class Expression {
public:
	virtual double eval() const = 0;

	virtual void print() const = 0;
};

class Number : public Expression {
private:
	const double num;
public:
	explicit Number(double num);

	double eval() const override;

	void print() const override;

	double getNum() const;
};

class BinaryOperator : public Expression {
protected:
	std::shared_ptr<Expression> left;
	std::shared_ptr<Expression> right;
public:
	BinaryOperator(const std::shared_ptr<Expression>& left, const std::shared_ptr<Expression>& right);

	double eval() const override;

	virtual double calculate(double left, double right) const = 0;
};

class UnaryOperator : public Expression {
protected:
	std::shared_ptr<Expression> exp;
public:
	explicit UnaryOperator(const std::shared_ptr<Expression>& exp);

	double eval() const override;

	virtual double calculate(double exp) const = 0;
};

class AdditionOperator : public BinaryOperator {
public:
	AdditionOperator(const std::shared_ptr<Expression>& left, const std::shared_ptr<Expression>& right);

	void print() const override;

	double calculate(double left, double right) const override;
};

class SubtractionOperator : public BinaryOperator {
public:
	SubtractionOperator(const std::shared_ptr<Expression>& left, const std::shared_ptr<Expression>& right);

	void print() const override;

	double calculate(double left, double right) const override;
};

class MultiplicationOperator : public BinaryOperator {
public:
	MultiplicationOperator(const std::shared_ptr<Expression>& left, const std::shared_ptr<Expression>& right);

	void print() const override;

	double calculate(double left, double right) const override;
};

class DivisionOperator : public BinaryOperator {
public:
	DivisionOperator(const std::shared_ptr<Expression>& left, const std::shared_ptr<Expression>& right);

	void print() const override;

	double calculate(double left, double right) const override;
};

class NegationOperator : public UnaryOperator {
public:
	NegationOperator(const std::shared_ptr<Expression>& exp);

	void print() const override;

	double calculate(double exp) const override;
};

#endif //EDUSANDBOX_CALC_H
