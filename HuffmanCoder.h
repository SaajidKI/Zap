/*
 *  HuffmanCoder.h
 *  Saajid Islam
 *  11/16/2022
 *
 *  Project 3 - Zap
 *
 *  Purpose: Class declaration for HuffmanCoder which contains the encoding
 *           and decoding text files functions. 
 */

#ifndef HUFFMAN_CODER_H
#define HUFFMAN_CODER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <map>
#include <queue>
#include <vector>

#include "HuffmanTreeNode.h"
#include "BinaryIO.h"

using namespace std;

class HuffmanCoder {
public:
    void encoder(string input_file, string output_file);
    void decoder(string input_file, string output_file);
private:
    map<char, int> count_freqs(istream &text);
    HuffmanTreeNode* build_tree(map<char, int> freqs);
    void gen_char_codes(string code, map<char, string> &char_codes,
                        HuffmanTreeNode* node);
    string encode_text(istream &text, map<char, string> char_codes);
    string serialize_tree(HuffmanTreeNode* root);

    HuffmanTreeNode* deserialize_tree(string serial_tree);
    HuffmanTreeNode* deser_tree_helper(string serial_tree, size_t &i);
    string decode_text(HuffmanTreeNode* root, string text);

    void delete_tree(HuffmanTreeNode* root);
    template<typename streamtype>
    void open_or_die(streamtype &stream, std::string file_name);
};

#endif
