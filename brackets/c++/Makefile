all: brackets brackettest

brackets : brackets.cpp
	g++-5 -g -Wall -Wextra -std=c++14 -o $@ $<


brackettest : brackettest.cpp brackets.cpp
	g++-5 -g -Wall -Wextra -std=c++14 -o $@ $<


test : brackettest
	./brackettest


clean :
	rm -f brackettest brackets
