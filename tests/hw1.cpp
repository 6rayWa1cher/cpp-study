//
// Created by Konstantin Grigoriev on 12/09/2019.
//
#define CATCH_CONFIG_MAIN

#include "../hw1/primefunc.h"
#include "../catch.hpp"

TEST_CASE("Primes are computed", "[isPrime]") {
	REQUIRE(!isPrime(1));
	REQUIRE(isPrime(2));
	REQUIRE(isPrime(5));
	REQUIRE(!isPrime(6));
	REQUIRE(!isPrime(42));
	REQUIRE(isPrime(17));
}