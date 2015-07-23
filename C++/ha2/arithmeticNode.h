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
    	Node* leftChild() const { return leftChild_; }
    	Node* rightChild() const { return rightChild_; }
    	Operation operation() const { return operation_; }
    	int line() const { return line_; }
    	int visit(IVisitor* vis) const { return vis->visit(this); }
private:
    	Node* const leftChild_;
    	Node* const rightChild_;
    	const Operation operation_;
    	const int line_;

};


#endif // ARITHMETICNODE_H
