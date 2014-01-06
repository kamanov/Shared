#ifndef NUMBERNODE_H
#define NUMBERNODE_H

#include "node.h"
#include "ivisitor.h"


class Number : public Node
{
	int value_;
public:
	 Number(int value) : value_(value) {}
	 int value() { return value_; }
	 int visit(IVisitor* vis) { return vis->visit(this); }
	
};

#endif // NUMBERNODE_H