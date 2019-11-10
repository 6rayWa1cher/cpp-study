//
// Created by 6rayWa1cher on 08.11.2019.
//

#ifndef EDUSANDBOX_RATIONAL_H
#define EDUSANDBOX_RATIONAL_H

#include <string>
#include <iostream>

class ArithmeticException : public std::runtime_error {
public:
	explicit ArithmeticException(const std::string& message);
};

class InputError : public std::runtime_error {
public:
	explicit InputError(const std::string& message);
};

class Rational {
private:
	int _numerator;
	int _denominator; // Always must be not negative
	void normalizeRational();

public:
	Rational();

	explicit Rational(int num);

	Rational(int num, int denom);

	int getNumerator() const {
		return _numerator;
	}

	int getDenominator() const {
		return _denominator;
	}

	std::string toString() const {
		return std::to_string(getNumerator()) + "/" + std::to_string(getDenominator());
	}

	friend Rational& operator*=(Rational& r1, const Rational& r2);

	friend Rational& operator+=(Rational& r1, const Rational& r2);

	explicit operator double();

	friend bool operator==(const Rational& lhs, const Rational& rhs);

	friend bool operator!=(const Rational& lhs, const Rational& rhs);
};

std::istream& operator>>(std::istream& istream, Rational& rational);

std::ostream& operator<<(std::ostream& ostream, const Rational& rational);

Rational& operator+=(Rational& r1, const Rational& r2);

Rational& operator*=(Rational& r1, const Rational& r2);

Rational operator-(const Rational& r);

Rational operator+(const Rational& r1, const Rational& r2);

Rational operator-(const Rational& r1, const Rational& r2);

Rational operator*(const Rational& r1, const Rational& r2);

bool operator==(const Rational& lhs, const Rational& rhs);

bool operator!=(const Rational& lhs, const Rational& rhs);

bool operator>(const Rational& lhs, const Rational& rhs);

#endif //EDUSANDBOX_RATIONAL_H
