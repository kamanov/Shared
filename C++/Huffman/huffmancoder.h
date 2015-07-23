#include <iostream>
#include <vector>
#include <map>
#include "streamreader.h"
#include "node.h"
#include "bufwriter.h"
#include "streamwriter.h"
#include <memory>

class HuffmanCoder
{
	const int number_of_symbols_;
    StreamReader reader_;
    BufWriter buf_writer_;
    StreamWriter writer_;
    void countFreqs(std::vector<unsigned int>& freqs_arr);
    void makeTable(Node* root, std::vector<std::vector<bool> > &table, std::vector<bool>& code);
    void writeCompressedData(std::vector<std::vector<bool> > &table);
    void writeHeaderToOutput(std::vector<unsigned int> & freqs_arr);
  public:
	
    HuffmanCoder(std::ifstream& input, std::ofstream& output);
    void startCompressing();

};
