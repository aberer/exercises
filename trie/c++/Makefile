all:
	g++  -g -std=c++14 -DTEST_CASE  -o opttrie_test opttrie_test.cpp

test : all
	./opttrie_test

opttrie:
	g++  -g -std=c++14 -o opttrie  opttrie.cpp

clean:
	rm *.o opttrie opttrie_test
