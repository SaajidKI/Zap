###
### Makefile for Zap Project
### Zap is a compression program that compresses text files
###
### Author: Saajid Islam

MAKEFLAGS += -L 
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3

zap: main.o HuffmanCoder.o HuffmanTreeNode.o BinaryIO.o
	$(CXX) $(LDFLAGS) -o zap $^

main.o: main.cpp HuffmanCoder.h
	$(CXX) $(CXXFLAGS) -c main.cpp

HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h HuffmanTreeNode.h BinaryIO.h
	$(CXX) $(CXXFLAGS) -c HuffmanCoder.cpp

unit_test: unit_test_driver.o HuffmanTreeNode.o phaseOne.o
	$(CXX) $(CXXFLAGS) $^

provide:
	provide comp15 proj3_zap \
				   README Makefile main.cpp \
				   HuffmanCoder.h HuffmanCoder.cpp \
				   test.zap test_output.txt

clean:
	rm main.o HuffmanCoder.o
