#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include <iostream>

#include "opttrie.cpp"


TEST_CASE("example test case", "[trie test]")
{
    Trie trie;

    trie.add("hack");
    trie.add("hackerrank");

    REQUIRE(trie.find("hac") == 2u);
    REQUIRE(trie.find("hak") == 0u);
}



TEST_CASE("adds substrings ", "[trie test]")
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


TEST_CASE("multilevel", "[trie test]")
{
    Trie trie;

    trie.add("aaaaaa");         //
    trie.add("abaaaa");
    trie.add("acaaaa");
    trie.add("aabaaa");         //
    trie.add("aacaaa");         //
    trie.add("aaabaa");         //
    trie.add("aaacaa");         //
    trie.add("aaaaba");         //
    trie.add("aaaaca");         //
    trie.add("aaaaab");         //
    trie.add("aaaaac");         //
    trie.add("a");
    trie.add("ab");
    trie.add("abc");
    trie.add("ac");

    REQUIRE(trie.find("a") == 15u);
    REQUIRE(trie.find("ab") == 3u);
    REQUIRE(trie.find("ac") == 2u);
    REQUIRE(trie.find("abc") == 1u);
}


TEST_CASE("including prefixes", "[trie test]")
{
    Trie trie;
    trie.add("aabbeerreerr");
    trie.add("aabbeerr");
    trie.add("aabb");

    trie.add("bbeerreerr");
    trie.add("bbeerr");
    trie.add("bb");

    REQUIRE(trie.find("a") == 3u);
    REQUIRE(trie.find("aa") == 3u);
    REQUIRE(trie.find("aabb") == 3u);
    REQUIRE(trie.find("aabbe") == 2u);
    REQUIRE(trie.find("b") == 3u);
    REQUIRE(trie.find("bb") == 3u);
    REQUIRE(trie.find("bbe") == 2u);
    REQUIRE(trie.find("aabbeerreerr") == 1u);
    REQUIRE(trie.find("bbeerreerr") == 1u);
}


TEST_CASE("including prefixes inverse", "[trie test]")
{
    Trie trie;
    trie.add("aabb");
    trie.add("aabbeerr");
    trie.add("aabbeerreerr");

    trie.add("bb");
    trie.add("bbeerr");
    trie.add("bbeerreerr");

    REQUIRE(trie.find("a") == 3u);
    REQUIRE(trie.find("aa") == 3u);
    REQUIRE(trie.find("aabb") == 3u);
    REQUIRE(trie.find("aabbe") == 2u);
    REQUIRE(trie.find("b") == 3u);
    REQUIRE(trie.find("bb") == 3u);
    REQUIRE(trie.find("bbe") == 2u);
    REQUIRE(trie.find("aabbeerreerr") == 1u);
    REQUIRE(trie.find("bbeerreerr") == 1u);
}


TEST_CASE("including prefixes mixed", "[trie test]")
{
    Trie trie;
    trie.add("aabbeerr");
    trie.add("aabb");
    trie.add("aabbeerreerr");

    trie.add("bbeerr");
    trie.add("bb");
    trie.add("bbeerreerr");

    REQUIRE(trie.find("a") == 3u);
    REQUIRE(trie.find("aa") == 3u);
    REQUIRE(trie.find("aabb") == 3u);
    REQUIRE(trie.find("aabbe") == 2u);
    REQUIRE(trie.find("b") == 3u);
    REQUIRE(trie.find("bb") == 3u);
    REQUIRE(trie.find("bbe") == 2u);
    REQUIRE(trie.find("aabbeerreerr") == 1u);
    REQUIRE(trie.find("bbeerreerr") == 1u);
}


TEST_CASE("not found", "[trie test]")
{
    Trie trie;
    trie.add("aabbeerr");
    REQUIRE(trie.find("b") == 0u);
}


TEST_CASE("empty trie", "[trie test]")
{
    Trie trie;
    REQUIRE(trie.find("b") == 0u);
}
