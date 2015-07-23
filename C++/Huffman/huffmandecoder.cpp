#include "huffmandecoder.h"
#include "tree.h"
#include "treewalker.h"


HuffmanDecoder::HuffmanDecoder(std::ifstream& input, std::ofstream& output)
    : number_of_symbols_(256)
    , reader_(input)
    , writer_(output)
{
}


void HuffmanDecoder::readFileHeader(std::vector<unsigned int> &freqs_arr)
{

    reader_.readVector(freqs_arr);

}

void HuffmanDecoder::writeDecompressedData(Node* p_root)
{
    TreeWalker tree_walker(p_root, writer_);

    while (reader_.hasNext()) {
        unsigned char byte = reader_.next();
        tree_walker.addByteToDecode(byte);
    }
}

void HuffmanDecoder::startDecompressing()
{

    std::vector<unsigned int> freqs_arr(number_of_symbols_, 0);
    readFileHeader(freqs_arr);

    std::unique_ptr<Node> p_root = Tree::makeTree(freqs_arr);

    writeDecompressedData(p_root.get());

}
