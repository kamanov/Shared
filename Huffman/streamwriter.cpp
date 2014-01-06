#include "streamwriter.h"

StreamWriter::StreamWriter(std::ofstream &ostream) : ostream_(ostream)
{

}

void StreamWriter::writeVector(const std::vector<unsigned int> &vect, unsigned int size)
{
    ostream_.write((char*)(&size), sizeof(size));
    unsigned char cnt = 0;
    while(true) {

        if(vect[cnt] != 0) {
            ostream_.put(cnt);
            ostream_.write((char*)(&vect[cnt]), sizeof(int));
        }

        cnt++;
        if(cnt == 0)
            break;
    }

}

void StreamWriter::write(unsigned char symbol)
{
    ostream_.put(symbol);
}
