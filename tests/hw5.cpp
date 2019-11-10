//
// Created by 6rayWa1cher on 08.11.2019.
//

#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../hw5/rational.h"

TEST_CASE("Rational tests", "[Rational]") {
	SECTION("Constructors + << test") {
		std::ostringstream ss;
		Rational r1, r2(42), r3(7, 5);
		ss << r1;
		CHECK("0/1" == ss.str());
		ss = std::ostringstream();
		ss << r2;
		CHECK("42/1" == ss.str());
		ss = std::ostringstream();
		ss << r3;
		CHECK("7/5" == ss.str());
		ss = std::ostringstream();
		CHECK_THROWS(Rational(7, 0));
	} SECTION(">> test") {
		Rational r1, r2;
		std::istringstream ss("4/13 4/0");
		ss >> r1;
		CHECK_THROWS(ss >> r2);
	} SECTION("== and > test") {
		Rational r1(4, 5), r2(6, 7);
		CHECK_FALSE(r1 > r2);
		CHECK(r2 > r1);
		CHECK_FALSE(r1 == r2);
		CHECK(Rational(4, 5) == r1);
		CHECK_FALSE(Rational(-4, 5) == r1);
	} SECTION("+= test") {
		Rational r1(4, 5), r2(5, 7);
		r1 += r1;
		CHECK(Rational(8, 5) == r1);
		r1 += r2;
		CHECK(Rational(81, 35) == r1);
		Rational r3(4, 35);
		r1 += r3;
		CHECK(Rational(17, 7) == r1);
	} SECTION("*= test") {
		Rational r1(4, 5), r2(6, 7);
		r1 *= r1;
		CHECK(Rational(16, 25) == r1);
		r1 *= r2;
		CHECK(Rational(96, 175) == r1);
		Rational r3(175, 26);
		r1 *= r3;
		CHECK(Rational(48, 13) == r1);
	} SECTION("Negative rational test") {
		Rational r1(-5, -7), r2(-5, 7), r3(5, -7);
		CHECK(Rational(5, 7) == r1);
		CHECK(Rational(-5, 7) == r2);
		CHECK(Rational(-5, 7) == r3);
		r1 += r2;
		CHECK(Rational(0, 1) == r1);
		Rational r4(49, 25);
		r3 *= r4;
		CHECK(Rational(-7, 5) == r3);
		r2 += r3;
		CHECK(Rational(-74, 35) == r2);
	} SECTION("+, -, * and -r test") {
		Rational r1(4, 5), r2(6, 7);
		CHECK(Rational(58, 35) == r1 + r2);
		CHECK(Rational(-2, 35) == r1 - r2);
		CHECK(Rational(24, 35) == r1 * r2);
		CHECK(Rational(-24, 35) == r1 * -r2);
	} SECTION("to double") {
		Rational r1(3, 5), r2(1, 3);
		CHECK(0.6 == static_cast<double>(r1));
		CHECK(1.0 / 3.0 == Approx(static_cast<double>(r2)));
	}
}