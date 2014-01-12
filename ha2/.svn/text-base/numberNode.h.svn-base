#ifndef NUMBERNODE_H
#define NUMBERNODE_H

#include "node.h"
#include "ivisitor.h"


class Number : public Node
{
    	const int value_;
public:
	 Number(int value) : value_(value) {}
     	int value() const { return value_; }
     	int visit(IVisitor* vis) const { return vis->visit(this); }
		
};

#endif // NUMBERNODE_H
