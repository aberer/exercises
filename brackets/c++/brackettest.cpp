#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include "brackets.cpp"


// _____________________________________________________________________________
TEST_CASE("emtpy", "[bracket test]")
{
    REQUIRE(isBalanced(""));
}


// _____________________________________________________________________________
TEST_CASE("default match", "[bracket test]")
{
    REQUIRE(isBalanced("()"));
    REQUIRE(isBalanced("{}"));
    REQUIRE(isBalanced("[]"));

    REQUIRE(isBalanced("[[]]"));
    REQUIRE(isBalanced("[][]"));

    REQUIRE(isBalanced("([{}])[]{{}}"));
    REQUIRE(isBalanced("{[()]}[[]]{{{{}}}}"));
}


// _____________________________________________________________________________
TEST_CASE("mismatch", "[bracket test]")
{
    REQUIRE(!isBalanced(")"));
    REQUIRE(!isBalanced("]"));
    REQUIRE(!isBalanced("}"));

    // enclosed by matching
    REQUIRE(!isBalanced("(})"));

    // end not matching
    REQUIRE(!isBalanced("[]{"));

    // start not matching
    REQUIRE(!isBalanced("}[]"));
}
