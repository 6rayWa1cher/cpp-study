//
// Created by 6rayWa1cher on 18.02.2020.
//

#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../hw8/calc.h"

TEST_CASE("AdditionTest", "[AdditionOperator]") {
	std::shared_ptr<Number> left = std::make_shared<Number>(2.0);
	std::shared_ptr<Number> right = std::make_shared<Number>(3.0);
	std::shared_ptr<AdditionOperator> addition = std::make_shared<AdditionOperator>(left, right);
	CHECK(Approx(5.0) == addition->eval());
	// https://stackoverflow.com/questions/3803465/how-to-capture-stdout-stderr-with-googletest
	// This can be an ofstream as well or any other ostream
	std::stringstream buffer;
	// Save cout's buffer here
	std::streambuf *sbuf = std::cout.rdbuf();
	// Redirect cout to our stringstream buffer or any other ostream
	std::cout.rdbuf(buffer.rdbuf());
	addition->print();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);
	CHECK("(2+3)" == buffer.str());
}

TEST_CASE("SubtractionTests", "[SubtractionOperator]") {
	std::shared_ptr<Number> left = std::make_shared<Number>(2.0);
	std::shared_ptr<Number> right = std::make_shared<Number>(3.0);
	std::shared_ptr<SubtractionOperator> sub = std::make_shared<SubtractionOperator>(left, right);
	CHECK(Approx(-1.0) == sub->eval());
	// This can be an ofstream as well or any other ostream
	std::stringstream buffer;
	// Save cout's buffer here
	std::streambuf *sbuf = std::cout.rdbuf();
	// Redirect cout to our stringstream buffer or any other ostream
	std::cout.rdbuf(buffer.rdbuf());
	sub->print();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);
	CHECK("(2-3)" == buffer.str());
}

TEST_CASE("MultiplicationTests", "[MultiplicationOperator]") {
	std::shared_ptr<Number> left = std::make_shared<Number>(2.0);
	std::shared_ptr<Number> right = std::make_shared<Number>(3.0);
	std::shared_ptr<MultiplicationOperator> multiply = std::make_shared<MultiplicationOperator>(left, right);
	CHECK(Approx(6.0) == multiply->eval());
	// This can be an ofstream as well or any other ostream
	std::stringstream buffer;
	// Save cout's buffer here
	std::streambuf *sbuf = std::cout.rdbuf();
	// Redirect cout to our stringstream buffer or any other ostream
	std::cout.rdbuf(buffer.rdbuf());
	multiply->print();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);
	CHECK("(2*3)" == buffer.str());
}

TEST_CASE("DivisionTests", "[DivisionOperator]") {
	std::shared_ptr<Number> left = std::make_shared<Number>(2.0);
	std::shared_ptr<Number> right = std::make_shared<Number>(3.0);
	std::shared_ptr<DivisionOperator> division = std::make_shared<DivisionOperator>(left, right);
	CHECK(Approx(2.0 / 3.0) == division->eval());
	// This can be an ofstream as well or any other ostream
	std::stringstream buffer;
	// Save cout's buffer here
	std::streambuf *sbuf = std::cout.rdbuf();
	// Redirect cout to our stringstream buffer or any other ostream
	std::cout.rdbuf(buffer.rdbuf());
	division->print();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);
	CHECK("(2/3)" == buffer.str());
}

TEST_CASE("NegationTests", "[NegationOperator]") {
	std::shared_ptr<Number> exp = std::make_shared<Number>(42.0);
	std::shared_ptr<NegationOperator> neg = std::make_shared<NegationOperator>(exp);
	CHECK(Approx(-42.0) == neg->eval());
	// This can be an ofstream as well or any other ostream
	std::stringstream buffer;
	// Save cout's buffer here
	std::streambuf *sbuf = std::cout.rdbuf();
	// Redirect cout to our stringstream buffer or any other ostream
	std::cout.rdbuf(buffer.rdbuf());
	neg->print();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);
	CHECK("(-42)" == buffer.str());
}

TEST_CASE("NumberTests", "[Number]") {
	Number n(42.0);
	CHECK(Approx(42.0) == n.eval());
	// This can be an ofstream as well or any other ostream
	std::stringstream buffer;
	// Save cout's buffer here
	std::streambuf *sbuf = std::cout.rdbuf();
	// Redirect cout to our stringstream buffer or any other ostream
	std::cout.rdbuf(buffer.rdbuf());
	n.print();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);
	CHECK("42" == buffer.str());
}

TEST_CASE("ComplexEvaluationTests", "[calc]") {
	SECTION("Test #1") {
		// (4*(-(5-3)))/(2+3)
		std::shared_ptr<Expression> e = std::make_shared<DivisionOperator>(
				std::make_shared<MultiplicationOperator>(
						std::make_shared<Number>(4.0),
						std::make_shared<NegationOperator>(
								std::make_shared<SubtractionOperator>(
										std::make_shared<Number>(5.0),
										std::make_shared<Number>(3.0)
								)
						)
				),
				std::make_shared<AdditionOperator>(
						std::make_shared<Number>(2.0),
						std::make_shared<Number>(3.0)
				)
		);
		CHECK(Approx(-1.6) == e->eval());
		// This can be an ofstream as well or any other ostream
		std::stringstream buffer;
		// Save cout's buffer here
		std::streambuf *sbuf = std::cout.rdbuf();
		// Redirect cout to our stringstream buffer or any other ostream
		std::cout.rdbuf(buffer.rdbuf());
		e->print();
		// When done redirect cout to its old self
		std::cout.rdbuf(sbuf);
		CHECK("((4*(-(5-3)))/(2+3))" == buffer.str());
	}
}