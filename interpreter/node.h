#ifndef NODE_H
#define NODE_H

class IVisitor;

class Node
{
public:
	virtual int visit(IVisitor* vis) = 0;
	virtual ~Node() {};
};

#endif //NODE_H
