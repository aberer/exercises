#! /usr/bin/python3

from trie import Trie
from unittest import TestCase
from copy import deepcopy
import pdb


class TrieTest(TestCase):

    # __________________________________________________________________________
    def setUp(self):
        self._testTrie = Trie("",
                              [Trie("a", [Trie("bl"), Trie("c")]),
                               Trie("b", [Trie("ca"), Trie("a")])])

    # __________________________________________________________________________
    def testGetNumberOfLeaves(self):
        self.assertEqual(self._testTrie.getNumberOfLeaves(), 4)
        self.assertEqual(Trie().getNumberOfLeaves(), 1)

    # __________________________________________________________________________
    def testFind(self):
        self.assertEqual(self._testTrie.find("ab"), 1)
        self.assertEqual(self._testTrie.find("a"), 2)


    # __________________________________________________________________________
    def testAddToExisting(self):

        return()
        trie = deepcopy(self._testTrie)

        trie.add("cd")
        self.assertEqual(trie.find("cd"), 1)

        trie.add("ce")
        self.assertEqual(trie.find("ce"), 1)
        self.assertEqual(trie.find("c"), 2)

        trie.add("bcad")

    # __________________________________________________________________________
    def testAddDeNovo(self):
        trie = Trie()

        trie.add("abl")
        trie.add("ac")
        trie.add("bca")
        trie.add("baa")

        self.assertEqual(trie.find("b"), 2)
        self.assertEqual(trie.find("a"), 2)
        self.assertEqual(trie.find("abl"), 1)
        self.assertEqual(trie.find("ac"), 1)
        self.assertEqual(trie.find("bca"), 1)
        self.assertEqual(trie.find("baa"), 1)

    # __________________________________________________________________________
    def testAddSubstring(self):
        trie = Trie()

        trie.add("aberer")
        trie.add("ab")
        trie.add("a")

        self.assertEqual(trie.find("a"), 3)
        self.assertEqual(trie.find("ab"), 2)
        self.assertEqual(trie.find("aberer"), 1)

        trie.add("abe")
        self.assertEqual(trie.find("abe"), 2)


    # __________________________________________________________________________
    def testExample(self):
        trie = Trie()

        trie.add("hack")
        trie.add("hackerrank")

        self.assertEqual(trie.find("hac"), 2)
        self.assertEqual(trie.find("hak"), 0)
