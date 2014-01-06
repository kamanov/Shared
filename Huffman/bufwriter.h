#ifndef BUFWRITER_H
#define BUFWRITER_H

#include <fstream>
#include <vector>

class BufWriter
{
    std::ostream& ofstream_;
    unsigned char buffer_;
    int bit_count_;
    void writeBufToStream();
public:
    BufWriter(std::ofstream& stream);
    void close();
    void write(std::vector<bool>& bits_vector);

};

#endif // BUFWRITER_H
