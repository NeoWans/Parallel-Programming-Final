CC = gcc
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Ofast -Iinc -pthread
OBJ = constant.o
INC = constant.hh

vpath %.hh inc
vpath %.cc src

.PHONY: all
all: list bitset bitset_thread

list: $(OBJ) $(INC) list_matrix.o list.cc
	$(CXX) $(CXXFLAGS) -o list $(OBJ) list_matrix.o $$(find -name 'list.cc')

bitset: $(OBJ) $(INC) bitset_matrix.o bitset.cc
	$(CXX) $(CXXFLAGS) -o bitset $(OBJ) bitset_matrix.o $$(find -name 'bitset.cc')

bitset_thread: $(OBJ) $(INC) bitset_matrix_thread.o bitset_thread.cc
	$(CXX) $(CXXFLAGS) -o bitset_thread $(OBJ) bitset_matrix_thread.o $$(find -name 'bitset_thread.cc')

list_matrix.o: list_matrix.hh list_matrix.cc
	$(CXX) $(CXXFLAGS) -c $$(find -name 'list_matrix.cc')

bitset_matrix.o: bitset_matrix.hh bitset_matrix.cc
	$(CXX) $(CXXFLAGS) -c $$(find -name 'bitset_matrix.cc')

bitset_matrix_thread.o: bitset_matrix_thread.hh bitset_matrix_thread.cc
	$(CXX) $(CXXFLAGS) -c $$(find -name 'bitset_matrix_thread.cc')

constant.o: constant.hh constant.cc
	$(CXX) $(CXXFLAGS) -c $$(find -name 'constant.cc')

.PHONY: clean
clean: 
	rm -rf *.o