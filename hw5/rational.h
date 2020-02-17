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

template<typename T>
class Rational {
private:
	T _numerator;
	T _denominator; // Always must be not negative
	void normalizeRational();

public:
	Rational();

	explicit Rational(T num);

	Rational(T num, T denom);

	T getNumerator() const {
		return _numerator;
	}

	T getDenominator() const {
		return _denominator;
	}

	std::string toString() const {
		return std::to_string(getNumerator()) + "/" + std::to_string(getDenominator());
	}

	template<typename J>
	friend Rational<J>& operator*=(Rational<J>& r1, const Rational<J>& r2);

	template<typename J>
	friend Rational<J>& operator+=(Rational<J>& r1, const Rational<J>& r2);

	explicit operator double();

//	template<typename L, typename R>
//	friend bool operator==(const Rational<L>& lhs, const Rational<R>& rhs);
//
//	template<typename L, typename R>
//	friend bool operator!=(const Rational<L>& lhs, const Rational<R>& rhs);
	bool operator==(const Rational& rhs) const;

	bool operator!=(const Rational& rhs) const;
};

template<typename T>
std::istream& operator>>(std::istream& istream, Rational<T>& rational);

template<typename T>
std::ostream& operator<<(std::ostream& ostream, const Rational<T>& rational);

template<typename T>
Rational<T>& operator+=(Rational<T>& r1, const Rational<T>& r2);

template<typename T>
Rational<T>& operator*=(Rational<T>& r1, const Rational<T>& r2);

template<typename T>
Rational<T> operator-(const Rational<T>& r);

template<typename T>
Rational<T> operator+(const Rational<T>& r1, const Rational<T>& r2);

template<typename T>
Rational<T> operator-(const Rational<T>& r1, const Rational<T>& r2);

template<typename T>
Rational<T> operator*(const Rational<T>& r1, const Rational<T>& r2);

//template<typename T>
//extern bool operator==(const Rational<T>& lhs, const Rational<T>& rhs);
//
//template<typename T>
//extern bool operator!=(const Rational<T>& lhs, const Rational<T>& rhs);
//
template<typename T>
bool operator>(const Rational<T>& lhs, const Rational<T>& rhs);

#endif //EDUSANDBOX_RATIONAL_H
