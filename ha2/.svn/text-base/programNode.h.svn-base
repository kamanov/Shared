#ifndef PROGRAMNODE_H
#define PROGRAMNODE_H

#include "node.h"
#include "ivisitor.h"

class Body;

class Program : public Node
{
    	Body* const body_;
public:
	Program(Body* body) 
		: body_(body) 
	{}
	~Program() { delete body_;}
    	Body* body() const { return body_; }
    	int visit(IVisitor* vis) const { return vis->visit(this); }

};


#endif // PROGRAMNODE_H






