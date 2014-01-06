#ifndef PROGRAMNODE_H
#define PROGRAMNODE_H

#include "node.h"
#include "ivisitor.h"

class Body;

class Program : public Node
{
	Body* body_;
public:
	Program(Body* body) 
		: body_(body) 
	{}
	~Program() { delete body_;}
	Body* body() { return body_; }
	int visit(IVisitor* vis) { return vis->visit(this); }

};


#endif // PROGRAMNODE_H






