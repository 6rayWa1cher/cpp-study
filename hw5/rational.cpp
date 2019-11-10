//
// Created by 6rayWa1cher on 08.11.2019.
//

#include "rational.h"

ArithmeticException::ArithmeticException(const std::string& message) : runtime_error(message) {

}


InputError::InputError(const std::string& message) : runtime_error(message) {

}


int gcd(int a, int b) {
	assert(a >= 0 && b >= 0);
	while (a != 0 && b != 0) {
		if (a > b) {
			a %= b;
		} else {
			b %= a;
		}
	}
	return a + b;
}

int lcm(int a, int b) {
	return abs(a * b) / gcd(a, b);
}

std::istream& operator>>(std::istream& istream, Rational& rational) {
	int a, b;
	char slash;
	istream >> a >> slash >> b;
	if (istream) {
		try {
			rational = Rational(a, b);
		} catch (ArithmeticException& e) {
//			istream.clear(std::ios_base::badbit);
			throw e;
		}
	} else {
		throw InputError("Bad rational");
	}
	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Rational& rational) {
	ostream << rational.toString();
	return ostream;
}

Rational& operator*=(Rational& r1, const Rational& r2) {
	r1._numerator *= r2.getNumerator();
	r1._denominator *= r2.getDenominator();
	r1.normalizeRational();
	return r1;
}

Rational& operator+=(Rational& r1, const Rational& r2) {
	int denominator = r1.getDenominator() == r2.getDenominator() ?
	                  r1.getDenominator() :
	                  lcm(r1.getDenominator(), r2.getDenominator());
	r1._numerator = (denominator / r1.getDenominator()) * r1.getNumerator() +
	                (denominator / r2.getDenominator()) * r2.getNumerator();
	r1._denominator = denominator;
	r1.normalizeRational();
	return r1;
}

Rational operator-(const Rational& r) {
	return {-r.getNumerator(), r.getDenominator()};
}

Rational operator+(const Rational& r1, const Rational& r2) {
	Rational r = r1;
	r += r2;
	return r;
}

Rational operator-(const Rational& r1, const Rational& r2) {
	return r1 + (-r2);
}

Rational operator*(const Rational& r1, const Rational& r2) {
	Rational r = r1;
	r *= r2;
	return r;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
	return lhs._numerator == rhs._numerator &&
	       lhs._denominator == rhs._denominator;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
	return !(rhs == lhs);
}

bool operator>(const Rational& lhs, const Rational& rhs) {
	int a = lhs.getNumerator(), b = lhs.getDenominator(),
			c = rhs.getNumerator(), d = rhs.getDenominator();
	return a * d > c * b;
}

Rational::Rational(int num, int denom) {
	if (denom == 0) {
		throw ArithmeticException("Denominator is zero");
	}
	this->_numerator = num;
	this->_denominator = denom;
	normalizeRational();
}

Rational::Rational(int num) : _numerator(num), _denominator(1) {}

Rational::Rational() : _numerator(0), _denominator(1) {}

void Rational::normalizeRational() {
	if (this->getDenominator() < 0) {
		this->_numerator *= -1;
		this->_denominator *= -1;
	}
	if (this->getNumerator() == 0) {
		this->_denominator = 1;
		return;
	} else if (this->getNumerator() > 0) {
		int gcdv = gcd(this->getNumerator(), this->getDenominator());
		this->_numerator /= gcdv;
		this->_denominator /= gcdv;
	} else {
		int gcdv = gcd(-this->getNumerator(), this->getDenominator());
		this->_numerator /= gcdv;
		this->_denominator /= gcdv;
	}
}

Rational::operator double() {
	return static_cast<double>(this->getNumerator()) / static_cast<double>(this->getDenominator());
}
