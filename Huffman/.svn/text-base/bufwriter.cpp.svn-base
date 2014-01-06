#include "bufwriter.h"


BufWriter::BufWriter(std::ofstream& stream)
    : ofstream_(stream)
    , buffer_(0)
    , bit_count_(0)
{
}

void BufWriter::close()
{
    if (bit_count_ != 0) {
        ofstream_.put(buffer_);
    }

}


void BufWriter::writeBufToStream()
{
    ofstream_.put(buffer_);
    buffer_ = 0;
    bit_count_ = 0;
}

void BufWriter::write(std::vector<bool>& bits_vector)
{
    unsigned int code_size = bits_vector.size();

    for(unsigned int i=0; i < code_size; i++) {
            buffer_ = buffer_ | bits_vector[i] << bit_count_;
            bit_count_++;
            if(bit_count_ == 8) {
                writeBufToStream();
            }
    }

}

