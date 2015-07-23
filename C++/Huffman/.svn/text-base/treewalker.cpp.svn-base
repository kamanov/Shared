#include "treewalker.h"



TreeWalker::TreeWalker(Node* p_root, StreamWriter &writer)
    : writer_(writer)
    , p_root_(p_root)
    , letter_count_(0)
    , curr_node_(p_root)
    , is_decode_all_(false)
{
    if(p_root_->isLeaf())
        processList();
}

void TreeWalker::addByteToDecode(unsigned char byte)
{


        for(int i = 0; i < 8; i++) {

            if (!is_decode_all_) {


                if (((byte >> i) & 1) == 1)
                    curr_node_ = curr_node_->right_child_;
                else
                    curr_node_ = curr_node_->left_child_;

                if (curr_node_->isLeaf())
                    processList();

            }

        }



}


void TreeWalker::processList()
{
    writer_.write(curr_node_->symbol_);
    curr_node_ = p_root_;
    letter_count_++;
    if (letter_count_ == p_root_->freq_)
        is_decode_all_ = true;

}
