#include "tree.h"
#include <queue>

std::unique_ptr<Node> Tree::makeTree(std::vector<unsigned int>& freqs_arr)
{

	auto compare = [](Node* lhs, Node* rhs)->bool{return (lhs->freq_ > rhs->freq_);};
    std::priority_queue<Node*, std::vector<Node*>, decltype(compare)>  queue(compare);
    unsigned int symbols_amount = 0;
    unsigned int size = freqs_arr.size();
    for(unsigned int i =0; i < size; i++)
	{
		if(freqs_arr[i] != 0) {
			queue.push(new Node(freqs_arr[i], i));
			symbols_amount++;
        }
	}
	

    for(unsigned int i = 0; i < symbols_amount - 1; i++) {
		Node* left = queue.top();
		queue.pop();
        Node* right = queue.top();
		queue.pop();
        queue.push(new Node(left->freq_ + right->freq_,0, right, left));
	}
    return std::unique_ptr<Node>(queue.top());
}
