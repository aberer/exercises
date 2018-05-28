#!/usr/bin/python3

import math
import os
import random
import re
import sys
import itertools
import cProfile



# ______________________________________________________________________________
class Trie:
    __slots__ = ("__prefix", "__children")

    # __________________________________________________________________________
    def __init__(self, prefix = "", children = None):
        self.__prefix = prefix
        self.__children = children

    # __________________________________________________________________________
    @property
    def children(self):
        if not self.__children:
            return []
        elif isinstance(self.__children, Trie):
            return [self.__children]
        else:
            return self.__children

    # __________________________________________________________________________
    def getNumberOfLeaves(self):
        if bool(self.children):
            return sum(x.getNumberOfLeaves() for x in self.children)
        else:
            return 1



    # __________________________________________________________________________
    def getChildAndPrefix(self, partToMatch):

        if not self.__children:
            return (None, None)
        elif isinstance(self.__children, Trie):
            p = os.path.commonprefix((self.__children.__prefix, partToMatch))
            return (self.__children, p) if len(p) > 0 else (None, None)
        else:
            return next(
                ((x,y) for (x,y) in
                 ((x, os.path.commonprefix((x.__prefix, partToMatch))) \
                  for x in self.children) \
                 if len(y) > 0),
                (None, None))


    # __________________________________________________________________________
    def _traverse(self, queryString, start):

        child, commonPrefix = self.getChildAndPrefix(queryString[start:])

        if child:
            if len(child.__prefix) == len(commonPrefix):
                return child._traverse(queryString, start + len(commonPrefix))
            else:
                return (child, start, start + len(commonPrefix))
        else:
            return (self, start, start)

    # __________________________________________________________________________
    def find(self, part):
        match, _, matchLength = self._traverse(part, 0)

        if not(part):
            return self.getNumberOfLeaves()
        elif matchLength < len(part):
            return 0
        else:
            return match.getNumberOfLeaves()


    # __________________________________________________________________________
    def __append(self, trie):
        if not self.__children:
            self.__children = [trie]
        elif isinstance(self.__children, Trie):
            self.__children = [self.__children, trie]
        else:
            self.__children.append(trie)

    # __________________________________________________________________________
    def add(self, contact):

        matchingNode, submatchStart, submatchEnd  = self._traverse(contact, 0)
        remainOfQuery = contact[submatchEnd:]
        submatch = contact[submatchStart:submatchEnd]

        if submatch == matchingNode.__prefix:
            # contact to add has a prefix in the current trie
            if bool(matchingNode.__prefix) and not bool(matchingNode.__children):
                matchingNode.__append(Trie())
            matchingNode.__append(Trie(remainOfQuery))
        elif submatchStart == submatchEnd:
            if not bool(matchingNode.__children):
                matchingNode.__append(Trie())

            matchingNode.__append(Trie(remainOfQuery))
        else:
            # we need to split the matching node
            remainOfExisting = matchingNode.__prefix[len(submatch):]
            matchingNode.__children = [
                Trie(remainOfExisting, matchingNode.__children),
                Trie(remainOfQuery)]
            matchingNode.__prefix = submatch

    # __________________________________________________________________________
    def __str__(self):
        return self.__prefix + "(" + ",".join(str(s) for s in self.__children) + ")"  \
            if bool(self.__children) \
               else  self.__prefix


# ______________________________________________________________________________
def main():
    trie = Trie()

    n = int(input())

    for n_itr in range(n):
        opContact = input().split()

        op = opContact[0]

        contact = opContact[1]

        if op == "add":
            trie.add(contact)
        elif op == "find":
            print(trie.find(contact))




# ______________________________________________________________________________
if __name__ == '__main__':
    main()
    # cProfile.run("main()")
