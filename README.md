########################################################
# README
# CS 15
# Project 3: Zap
# Name: Saajid Islam
########################################################

# Compile/run:

Compile using:
    make zap (or just make)
Run executable with:
    ./zap [zap | unzap] inputFile outputFile

# Program Purpose:

Zap is an implementation of a compression program which reduces
the number of bits needed to represent some data. It can compress
text files by storing the chars as binary code as well as decompress
binary code files back into ASCII text.

# Acknowledgements:

For this project, I was able to do a majority of the coding by myself,
using previous projects as a reference. But I did discuss some initial ideas
with other students in the class and worked together on designing some of the
functions. I also used the C++ reference site for some of my functions to
learn about certain features and built-in functions that I could use to 
modularize my code further and make it more efficient.

# Files:

main.cpp:
    Makes an instance of the HuffmanCoder class and runs either the encode 
    function or decode function based on the arguments passed in.

HuffmanCoder.cpp:
    Implementation of HuffmanCoder class. Main functionality is either to
    encode or decode a given file based on what function is called and store
    the output into a new file.

HuffmanCoder.h:
    Interface of HuffmanCoder class.

test.zap:
    Test file that stores the output from zapping (i.e. encoding) a file.
    Last tested file was sentences.txt.

test_output.txt:
    Test file that stores the output from unzapping (i.e. decoding) a file.
    Last tested file was sentences.txt.

# Data Structures:

The data structure used in this project were Huffman trees implemented via
binary trees and maps (i.e. hashes). The Huffman trees in this project were
used specifically for encoding and decoding ASCII to binary text. Huffman
coding first creates a tree using the frequencies of the character and then
generates a code for each character. Once the data is encoded, it can be
decoded using the same tree. Binary trees in general allow us to have
designated paths and allows us to connect related nodes. This was necessary for 
comparing frequencies and assigning the appropriate code for each character.
Maps made it really easy to store the chars and their associated data, whether
it be their frequencies or the corresponding codes. Since it dynamically 
created key value pairs, it made it really easy to keep track of existing
characters and adding new ones.

# Testing:

My initial testing phase was by writing a main function for PhaseOne to see
that all of the functions worked properly going forward. I would cout what
the functions returned and see if I got the intended results. Then, for
HuffmanCoder, I decided that writing my main.cpp and makefile would be my first
priority, since that would allow me to test all of the other functions. My
main was implemented in a similar manner to the one in MetroSim, so it was
easy to code and debug. Then I would write fucntions in HuffmanCoder.h and
HuffmanCoder.cpp concurrently so I could easily modify the parameters of any
function I make. Once I got my main.cpp working, my coding and testing process
was to first attempt to write one of the functions, then test it in my
implementation by printing using cout statements and seeing that it was the
desired value. Most of the functions I was able to implement fairly easily,
but for a couple, like decode_text, I had to really think through what my
functions were doing, since the bug I had (i.e. slightly wrong output) wasn't
immediately apparent. When it came to this, I would have a friend look over my
code to see if they catch something that I didn't realize (i.e. having a second
pair of eyes). At the end, when I was confident in my code, I would compare
output from my implementation with output from the provided implementation and
see that they match. I also used my first submission to the autograder to see
if I was missing anything obvious, or that I was on the right track. I also
tried out edge cases (such as empty files) on the reference implementation to
see how they handle errors and then work that into my code. Finally, once I
saw that my implementation had no differences from the implementation provided
to us, I was confident that I had no remaining errors.
