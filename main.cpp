/*
 *  main.cpp
 *  Saajid Islam
 *  11/16/2022
 *
 *  Project 3 - Zap
 *
 *  Purpose: Zap is an implementation of a compression program which reduces
 *           the number of bits needed to represent some data. It can compress
 *           and decompress text files by storing the chars as binary code.
 */

#include "HuffmanCoder.h"

int main(int argc, char* argv[])
{
    HuffmanCoder HuffmanCoder;

    if (argc == 4 and strcmp(argv[1], "zap") == 0) {
        HuffmanCoder.encoder(argv[2], argv[3]);
    } else if (argc == 4 and strcmp(argv[1], "unzap") == 0) {
        HuffmanCoder.decoder(argv[2], argv[3]);
    } else {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile" << endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
