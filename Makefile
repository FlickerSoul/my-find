CXX=g++
CXX_FLAGS=-g -std=c++2a
VALGRIND=valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes
.PHONY: all clean
TARGETS: myfind
all: $(TARGETS)


find_utils.o: find_utils.cc find_utils.hh
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

myfind: myfind.cc find_utils.o
	$(CXX) $(CXX_FLAGS) -o $@ $^	

test_find_utils.o: test_find_utils.cc find_utils.o
	$(CXX) $(CXX_FLAGS) -o $@ $^

clean:
	rm -rf *~ *.o $(TARGETS) *.dSYM