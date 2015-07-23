#ifndef STREAMWRITER_H
#define STREAMWRITER_H

#include <fstream>
#include <vector>

class StreamWriter
{
    std::ofstream& ostream_;
public:
    StreamWriter(std::ofstream& ostream);
    void writeVector(const std::vector<unsigned int>& vect, unsigned int size);
    void write(unsigned char symbol);
};

#endif // STREAMWRITER_H
