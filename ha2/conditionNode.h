#ifndef CONDITIONNODE_H
#define CONDITIONNODE_H

#include <string>
#include "node.h"
#include "ivisitor.h"


class Condition : public Node
{
    	Node* const leftChild_;
    	Node* const rightChild_;
    	const std::string operation_;
public:
	Condition(Node* leftChild, Node* rightChild, std::string& op) 
		: leftChild_(leftChild)
		, rightChild_(rightChild)
		, operation_(op)
	{}
	~Condition() { delete leftChild_; delete rightChild_; }
    	Node* leftChild() const { return leftChild_; }
    	Node* rightChild() const { return rightChild_; }
    	const std::string& operation() const { return operation_; }
    	int visit(IVisitor* vis) const{ return vis->visit(this); }

};

#endif //CONDITIONNODE_H






