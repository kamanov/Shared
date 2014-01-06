#ifndef NODE_H
#define NODE_H


struct Node 
{
    unsigned int freq_;
    unsigned char symbol_;
	Node* right_child_;
	Node* left_child_;

    Node(unsigned int freq, unsigned char symbol = 0, Node* rchild = 0, Node* lchild = 0)
		: freq_(freq)
		, symbol_(symbol)
		, right_child_(rchild)
		, left_child_(lchild) 
        {}

	~Node() 
	{
		if (right_child_ != 0)
			delete right_child_;
		if (left_child_ != 0)
			delete left_child_;
	}
	
	bool isLeaf() 
	{ 
		return left_child_ == 0;
	}	
	

};

#endif // NODE_H
