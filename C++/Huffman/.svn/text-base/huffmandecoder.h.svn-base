#ifndef HUFFMANDECODER_H
#define HUFFMANDECODER_H

#include "streamreader.h"
#include "streamwriter.h"
#include "fstream"
#include <vector>
#include <memory>
#include "node.h"

class HuffmanDecoder
{
    const int number_of_symbols_;
    StreamReader reader_;
    StreamWriter writer_;
    void readFileHeader(std::vector<unsigned int>& freqs_arr);
    void writeDecompressedData(Node* p_root);
public:
    HuffmanDecoder(std::ifstream& input, std::ofstream& output);
    void startDecompressing();
};

#endif // HUFFMANDECODER_H
