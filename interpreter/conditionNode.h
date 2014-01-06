#ifndef CONDITIONNODE_H
#define CONDITIONNODE_H

#include <string>
#include "node.h"
#include "ivisitor.h"


class Condition : public Node
{
	Node* leftChild_;
	Node* rightChild_;
	std::string operation_;
public:
	Condition(Node* leftChild, Node* rightChild, std::string& op) 
		: leftChild_(leftChild)
		, rightChild_(rightChild)
		, operation_(op)
	{}
	~Condition() { delete leftChild_; delete rightChild_; }
	Node* leftChild() { return leftChild_; }
	Node* rightChild() { return rightChild_; }
	std::string& operation() { return operation_; }
	int visit(IVisitor* vis) { return vis->visit(this); }

};

#endif //CONDITIONNODE_H






