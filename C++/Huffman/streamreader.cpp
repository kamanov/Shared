#include "streamreader.h"

StreamReader::StreamReader(std::ifstream& stream) : ifstream_(stream)
{
    ifstream_.seekg (0, ifstream_.end);
    file_length_ = ifstream_.tellg();
    ifstream_.seekg (0, ifstream_.beg);

}

bool StreamReader::hasNext()
{
    return ifstream_.tellg() != file_length_;
}

unsigned char StreamReader::next()
{
    return ifstream_.get();;
}

void StreamReader::setPosBegin()
{
    ifstream_.clear();
    ifstream_.seekg(0);
}

void StreamReader::readVector(std::vector<unsigned int> &freqs_arr)
{
    unsigned int size;
    ifstream_.read((char*)(&size), sizeof(int));
    for(unsigned int i =0; i < size; i++) {
        unsigned char symbol = ifstream_.get();
        unsigned int freq;
        ifstream_.read((char*)(&freq), sizeof(int));

        freqs_arr[symbol] = freq;
    }
}

