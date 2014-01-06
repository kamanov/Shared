#ifndef TREEWALKER_H
#define TREEWALKER_H

#include <memory>
#include "streamwriter.h"
#include "node.h"

class TreeWalker
{
    StreamWriter& writer_;
    Node* p_root_;
    unsigned long long letter_count_;
    Node* curr_node_;
    void processList();
    bool is_decode_all_;
public:
    TreeWalker(Node* p_root, StreamWriter& writer);
    void addByteToDecode(unsigned char byte);
};

#endif // TREEWALKER_H
