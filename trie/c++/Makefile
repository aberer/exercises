
all: opttrietest opttrie

test : opttrietest
	./opttrie_test

opttrietest : opttrie_test.cpp
	g++ -DTEST_CASE -Wall -Wextra -g -std=c++14 -o $@ $<

opttrie: opttrie.cpp
	g++ -Wall -Wextra -g -std=c++14 -o $@ $<

clean:
	rm *.o opttrie opttrie_test
