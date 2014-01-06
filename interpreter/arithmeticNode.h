#ifndef ARITHMETICNODE_H
#define ARITHMETICNODE_H

#include "node.h"
#include "ivisitor.h"

class Arithmetic : public Node
{
public:
	enum Operation{ADD, SUB, MUL, DIV};
	Arithmetic(Node* leftChild, Node* rightChild, Operation op, int line = 0) 
		: leftChild_(leftChild)
		, rightChild_(rightChild)
		, operation_(op)
		, line_(line)
	{}
	~Arithmetic() { delete leftChild_; delete rightChild_; }
	Node* leftChild() { return leftChild_; }
	Node* rightChild() { return rightChild_; }
	Operation operation() { return operation_; }
	int line() { return line_; }
	int visit(IVisitor* vis) { return vis->visit(this); }
private:
	Node* leftChild_;
	Node* rightChild_;
	Operation operation_;
	int line_;

};


#endif // ARITHMETICNODE_H
