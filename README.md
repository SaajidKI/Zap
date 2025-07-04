# Zap

**Zap** is a C++ command-line utility for file compression and decompression using Huffman coding. It can reduce the number of bits required to represent data by encoding characters into binary form, as well as decode them back into readable ASCII text.

## Compile & Run

To compile:
```bash
make
```

To run:
```bash
./zap [zap | unzap] <inputFile> <outputFile>
```

## Features

- `zap`: Compresses plain text files into binary format using Huffman coding
- `unzap`: Decompresses binary files back into their original ASCII representation
- Dynamically builds Huffman trees based on character frequencies
- Efficient lookup and encoding using maps for quick access to character codes

## Implementation Details

Zap uses a Huffman tree, which is a type of binary tree that encodes characters based on frequency, to minimize file size. Maps (hash tables) store character frequencies and encoding data, enabling fast access and efficient memory use. Each character is assigned a unique binary code, and the original text can be accurately reconstructed using the same tree structure.

## Testing & Validation

The program was thoroughly tested through iterative development. Each function was independently tested and verified using manual output comparison. Special attention was given to edge cases like empty files and uncommon characters. Output was validated against known correct results to ensure consistency and correctness.
