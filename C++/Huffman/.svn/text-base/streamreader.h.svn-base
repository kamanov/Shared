#ifndef STREAMREADER_H
#define STREAMREADER_H

#include <fstream>
#include <vector>

class StreamReader
{
    std::ifstream& ifstream_;
    int file_length_;
public:
    StreamReader(std::ifstream& stream);
    bool hasNext();
    unsigned char next();
    void setPosBegin();
    void readVector(std::vector<unsigned int> &freqs_arr);
};

#endif // STREAMREADER_H
