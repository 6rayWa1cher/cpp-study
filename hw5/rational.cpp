//
// Created by 6rayWa1cher on 08.11.2019.
//

#include "rational.h"

ArithmeticException::ArithmeticException(const std::string& message) : runtime_error(message) {

}


template<typename T>
int gcd(T a, T b) {
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

template<typename T>
int lcm(T a, T b) {
	return abs(a * b) / gcd(a, b);
}

template<typename T>
std::istream& operator>>(std::istream& istream, Rational<T>& rational) {
	T a, b;
	char slash = '/';
	istream >> a >> slash >> b;
	if (istream) {
		try {
			rational = Rational<T>(a, b);
		} catch (ArithmeticException& e) {
			istream.clear(std::ios_base::failbit);
		}
	}
	return istream;
}

template<typename T>
std::ostream& operator<<(std::ostream& ostream, const Rational<T>& rational) {
	ostream << rational.toString();
	return ostream;
}

template<typename T>
Rational<T>& operator*=(Rational<T>& r1, const Rational<T>& r2) {
	r1._numerator *= r2.getNumerator();
	r1._denominator *= r2.getDenominator();
	r1.normalizeRational();
	return r1;
}

template<typename T>
Rational<T>& operator+=(Rational<T>& r1, const Rational<T>& r2) {
	T denominator = r1.getDenominator() == r2.getDenominator() ?
	                r1.getDenominator() :
	                lcm(r1.getDenominator(), r2.getDenominator());
	r1._numerator = (denominator / r1.getDenominator()) * r1.getNumerator() +
	                (denominator / r2.getDenominator()) * r2.getNumerator();
	r1._denominator = denominator;
	r1.normalizeRational();
	return r1;
}

template<typename T>
Rational<T> operator-(const Rational<T>& r) {
	return {-r.getNumerator(), r.getDenominator()};
}

template<typename T>
Rational<T> operator+(const Rational<T>& r1, const Rational<T>& r2) {
	Rational<T> r = r1;
	r += r2;
	return r;
}

template<typename T>
Rational<T> operator-(const Rational<T>& r1, const Rational<T>& r2) {
	return r1 + (-r2);
}

template<typename T>
Rational<T> operator*(const Rational<T>& r1, const Rational<T>& r2) {
	Rational<T> r = r1;
	r *= r2;
	return r;
}

//template<typename L, typename R>
//bool operator==(const Rational<L>& lhs, const Rational<R>& rhs) {
//	if (typeid(L) != typeid(R)) return false;
//	return lhs._numerator == rhs._numerator &&
//	       lhs._denominator == rhs._denominator;
//}
//
//template<typename L, typename R>
//bool operator!=(const Rational<L>& lhs, const Rational<R>& rhs) {
//	if (typeid(L) != typeid(R)) return true;
//	return !(rhs == lhs);
//}

template<typename T>
bool operator>(const Rational<T>& lhs, const Rational<T>& rhs) {
	T a = lhs.getNumerator(), b = lhs.getDenominator(),
			c = rhs.getNumerator(), d = rhs.getDenominator();
	return a * d > c * b;
}

template<typename T>
Rational<T>::Rational(T num, T denom) {
	if (denom == 0) {
		throw ArithmeticException("Denominator is zero");
	}
	this->_numerator = num;
	this->_denominator = denom;
	normalizeRational();
}

template<typename T>
Rational<T>::Rational(T num) : _numerator(num), _denominator(1) {}

template<typename T>
Rational<T>::Rational() : _numerator(0), _denominator(1) {}

template<typename T>
void Rational<T>::normalizeRational() {
	if (this->getDenominator() < 0) {
		this->_numerator *= -1;
		this->_denominator *= -1;
	}
	if (this->getNumerator() == 0) {
		this->_denominator = 1;
		return;
	} else if (this->getNumerator() > 0) {
		T gcdv = gcd(this->getNumerator(), this->getDenominator());
		this->_numerator /= gcdv;
		this->_denominator /= gcdv;
	} else {
		T gcdv = gcd(-this->getNumerator(), this->getDenominator());
		this->_numerator /= gcdv;
		this->_denominator /= gcdv;
	}
}

template<typename T>
Rational<T>::operator double() {
	return static_cast<double>(this->getNumerator()) / static_cast<double>(this->getDenominator());
}

template<typename T>
bool Rational<T>::operator==(const Rational& rhs) const {
	return _numerator == rhs._numerator &&
	       _denominator == rhs._denominator;
}

template<typename T>
bool Rational<T>::operator!=(const Rational& rhs) const {
	return !(rhs == *this);
}

template
class Rational<int>;

template Rational<int> operator-(const Rational<int>& r);

template Rational<int> operator-(const Rational<int>& r1, const Rational<int>& r2);

template std::istream& operator>>(std::istream& istream, Rational<int>& rational);

template std::ostream& operator<<(std::ostream& ostream, const Rational<int>& rational);

template Rational<int>& operator+=(Rational<int>& r1, const Rational<int>& r2);

template Rational<int>& operator*=(Rational<int>& r1, const Rational<int>& r2);

template Rational<int> operator+(const Rational<int>& r1, const Rational<int>& r2);

template Rational<int> operator*(const Rational<int>& r1, const Rational<int>& r2);

template bool operator>(const Rational<int>& lhs, const Rational<int>& rhs);

template
class Rational<long>;

template Rational<long> operator-(const Rational<long>& r);

template Rational<long> operator-(const Rational<long>& r1, const Rational<long>& r2);

template std::istream& operator>>(std::istream& istream, Rational<long>& rational);

template std::ostream& operator<<(std::ostream& ostream, const Rational<long>& rational);

template Rational<long>& operator+=(Rational<long>& r1, const Rational<long>& r2);

template Rational<long>& operator*=(Rational<long>& r1, const Rational<long>& r2);

template Rational<long> operator+(const Rational<long>& r1, const Rational<long>& r2);

template Rational<long> operator*(const Rational<long>& r1, const Rational<long>& r2);

template bool operator>(const Rational<long>& lhs, const Rational<long>& rhs);