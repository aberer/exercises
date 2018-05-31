#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include <iostream>

#include "trie.cpp"


TEST_CASE("test the test", "[test]")
{
    Trie trie;

    trie.add("aberer");
    trie.add("abe");
    trie.add("a");
    trie.add("b");
    trie.add("be");
    trie.add("ber");

    REQUIRE(trie.find("a") == 3u);
    REQUIRE(trie.find("ab") == 2u);
    REQUIRE(trie.find("abe") == 2u);
    REQUIRE(trie.find("aberer") == 1u);
    REQUIRE(trie.find("b") == 3u);
    REQUIRE(trie.find("be") == 2u);
    REQUIRE(trie.find("ber") == 1u);
}
