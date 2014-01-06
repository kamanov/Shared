#include "huffmancoder.h"
#include "tree.h"
#include <memory>
#include "bufwriter.h"

HuffmanCoder::HuffmanCoder(std::ifstream& input, std::ofstream& output)
	: number_of_symbols_(256)
    , reader_(input)
    , buf_writer_(output)
    , writer_(output)
{
}

void  HuffmanCoder::countFreqs(std::vector<unsigned int>& freqs_arr)
{
	
    while (reader_.hasNext())
	{
        freqs_arr[reader_.next()]++;
	}

}

void HuffmanCoder::makeTable(Node* root, std::vector<std::vector<bool> > &table, std::vector<bool> &code)
{

    if (!root->isLeaf()) {
        code.push_back(0);
        makeTable(root->left_child_, table, code);
        code.push_back(1);
        makeTable(root->right_child_, table, code);
    }
    else {
        unsigned char c = root->symbol_;
        if (code.empty())
            code.push_back(0);
        table[c] = code;
    }
    code.pop_back();
}

void HuffmanCoder::writeHeaderToOutput(std::vector<unsigned int> &freqs_arr)
{
    unsigned int non_zero_symb = 0;
    for(int i = 0; i < number_of_symbols_; i++)
    {
        if(freqs_arr[i] != 0)
            non_zero_symb++;
    }
    writer_.writeVector(freqs_arr, non_zero_symb);
}

void HuffmanCoder::writeCompressedData(std::vector<std::vector<bool> > &table)
{
    reader_.setPosBegin();
    while (reader_.hasNext())
    {
        unsigned char symb = reader_.next();
        buf_writer_.write(table[symb]);
    }

    buf_writer_.close();

}
	

void HuffmanCoder::startCompressing()
{

    std::vector<unsigned int> freqs_arr(number_of_symbols_, 0);
	countFreqs(freqs_arr);
	
    std::unique_ptr<Node> p_root = Tree::makeTree(freqs_arr);

    std::vector<bool> code;
    std::vector<std::vector<bool> > sym_table(number_of_symbols_);

    makeTable(p_root.get(), sym_table, code);

    writeHeaderToOutput(freqs_arr);

    writeCompressedData(sym_table);



}
