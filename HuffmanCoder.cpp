/*
 *  HuffmanCoder.h
 *  Saajid Islam
 *  11/16/2022
 *
 *  Project 3 - Zap
 *
 *  Purpose: Function definitions for HuffmanCoder which contains the encoding
 *           and decoding text files functions. 
 */

#include "HuffmanCoder.h"

/* purpose:     encodes a given ASCII text file into compressed binary code
 * parameters:  file to encode and file to store output
 * returns:     none
 */
void HuffmanCoder::encoder(string input_file, string output_file)
{
    ifstream input;
    ofstream output;
    open_or_die(input, input_file);
    open_or_die(output, output_file);

    // checks if empty file
    if (input.peek() == ifstream::traits_type::eof())
        throw runtime_error("Cannot zap an empty file!");

    HuffmanTreeNode* hm_tree = build_tree(count_freqs(input));

    map<char, string> char_codes;
    gen_char_codes("", char_codes, hm_tree);

    input.clear();
    input.seekg(0, ios::beg); // resets the ifstream to the beginning

    string bitstring = encode_text(input, char_codes);
    string serial_tree = serialize_tree(hm_tree);

    BinaryIO file_writer;
    file_writer.writeFile(output_file, serial_tree, bitstring);

    cout << "Success! Encoded given text using " << bitstring.length()
         << " bits.\n";

    delete_tree(hm_tree);
    input.close();
    output.close();
}

/* purpose:     decodes a given compressed binary code file into ASCII text
 * parameters:  file to decode and file to store output
 * returns:     none
 */
void HuffmanCoder::decoder(string input_file, string output_file)
{
    ifstream input;
    ofstream output;
    open_or_die(input, input_file);
    open_or_die(output, output_file);
    
    BinaryIO file_reader;
    vector<string> encoded_text = file_reader.readFile(input_file);

    HuffmanTreeNode* hm_tree = deserialize_tree(encoded_text[0]);
    string decoded_text = decode_text(hm_tree, encoded_text[1]);

    output << decoded_text;

    delete_tree(hm_tree);
    input.close();
    output.close();
}

/* purpose:     counts how frequently a character appears in given text file
 * parameters:  input file to read in
 * returns:     map of characters and their corresponding frequencies
 */
map<char, int> HuffmanCoder::count_freqs(istream &text)
{
    map<char, int> freqs;
    
    while(not text.eof()) {
        string line;
        getline(text, line);
        for (size_t i = 0; i < line.length(); i++) {
            freqs[line[i]]++;
        }
        freqs['\n']++;
    }
    freqs['\n']--; // offsets '\n' by -1

    return freqs;
}

/* purpose:     builds an appropriate Huffman tree based on frequencies of chars
 * parameters:  map of characters and their corresponding frequencies
 * returns:     node pointer to the root of the Huffman tree
 */
HuffmanTreeNode* HuffmanCoder::build_tree(map<char, int> freqs)
{
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>,
                   NodeComparator> pq;

    for (auto x : freqs) {
        if (x.second != 0) {
            HuffmanTreeNode* node = new HuffmanTreeNode(x.first, x.second);
            pq.push(node);
        }
    }

    while (pq.size() > 1) {
        HuffmanTreeNode* node1 = pq.top();
        pq.pop();
        HuffmanTreeNode* node2 = pq.top();
        pq.pop();
        HuffmanTreeNode* node3 = new HuffmanTreeNode('\0', node1->get_freq() +
                                 node2->get_freq(), node1, node2);
        pq.push(node3);
    }

    return pq.top();
}

/* purpose:     generate binary codes for each char that appears in given map
 * parameters:  recursively generated code, reference to a map, and tree *
 * returns:     none, updates the map passed as a parameter
 */
void HuffmanCoder::gen_char_codes(string code, map<char, string> &char_codes,
                                  HuffmanTreeNode* node)
{
    if (node->isLeaf()) {
        char_codes[node->get_val()] = code;
        return;
    }
    gen_char_codes(code + "0", char_codes, node->get_left());
    gen_char_codes(code + "1", char_codes, node->get_right());
}

/* purpose:     encode the given text into binary using map of char codes
 * parameters:  text file to encode, map of chars and their corresponding codes
 * returns:     binary string that represents the encoded text
 */
string HuffmanCoder::encode_text(istream &text, map<char, string> char_codes)
{
    string binary_string = "";
    while(not text.eof()) {
        string line;
        getline(text, line);
        for (size_t i = 0; i < line.length(); i++) {
            binary_string += char_codes[line[i]];
        }
        binary_string += char_codes['\n'];
    }
    // offsets the extra newline character at the end
    binary_string.erase(binary_string.size() - char_codes['\n'].length());

    return binary_string;
}

/* purpose:     serialize a Huffman tree into a string
 * parameters:  Huffman tree to serialize
 * returns:     string representng the serialized Huffman tree
 */
string HuffmanCoder::serialize_tree(HuffmanTreeNode* root)
{
    stringstream ss;

    if (root == nullptr)
        return "";
    else if (root->isLeaf()) {
        ss << "L" << root->get_val();
        return ss.str();
    }
    ss << "I";
    
    ss << serialize_tree(root->get_left()) << serialize_tree(root->get_right());
    return ss.str();
}

/* purpose:     deserialize a string into a Huffman tree
 * parameters:  string to deserialize
 * returns:     node pointer to the root of the Huffman tree
 */
HuffmanTreeNode* HuffmanCoder::deserialize_tree(string serial_tree)
{
    size_t i = 0; //external counter
    return deser_tree_helper(serial_tree, i);
}

/* purpose:     helper function for deserialize_tree
 * parameters:  string to deserialize, reference to an external int counter
 * returns:     node pointer to the root of the Huffman tree
 */
HuffmanTreeNode* HuffmanCoder::deser_tree_helper(string serial_tree, size_t &i)
{
    if (serial_tree.size() == i)
        return nullptr;
    
    HuffmanTreeNode* node = nullptr;
    char c = serial_tree[i];
    
    i++;
    if (c == 'I') {
        node = new HuffmanTreeNode('\0', 0);
    } else if (c == 'L') {
        node = new HuffmanTreeNode(serial_tree[i], 0);
        i++;
        return node;
    }

    node->set_left(deser_tree_helper(serial_tree, i));
    node->set_right(deser_tree_helper(serial_tree, i));

    return node;
}

/* purpose:     decode the given file into ASCII text using a Huffman tree
 * parameters:  binary file to decode, Huffman tree to decode with
 * returns:     string representing the decoded tree
 */
string HuffmanCoder::decode_text(HuffmanTreeNode* root, string text)
{
    stringstream ss;
    HuffmanTreeNode* tree_traverser = root;
    
    for (size_t i = 0; i < text.length(); i++) {
        if (text[i] == '0')
            tree_traverser = tree_traverser->get_left();
        else // text[i] == '1'
            tree_traverser = tree_traverser->get_right();
        
        if (tree_traverser->isLeaf()) {
            ss << tree_traverser->get_val();
            tree_traverser = root;
        }
    }

    if (tree_traverser != root) {
        throw runtime_error("Encoding did not match Huffman tree.");
    }

    return ss.str();
}

/* purpose:     recycles heap allocated memory from tree nodes
 * parameters:  root of the tree to recycle
 * returns:     none
 */
void HuffmanCoder::delete_tree(HuffmanTreeNode* root)
{
    if (root == nullptr)
        return;

    delete_tree(root->get_left());
    delete_tree(root->get_right());

    delete root;
}

/* purpose:     attempts to open files, aborts if unable to open
 * parameters:  ifstream or ofstream and the associated file
 * returns:     none
 */
template<typename streamtype>
void HuffmanCoder::open_or_die(streamtype &stream, string file_name)
{
    stream.open(file_name);
    if (not stream.is_open())
        throw runtime_error("Unable to open file " + file_name);
}
