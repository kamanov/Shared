#ifndef IOFUNCTIONSNODE_H
#define IOFUNCTIONSNODE_H

#include "node.h"
#include "ivisitor.h"


class PrintFunction : public Node
{
	Node* printExpr_;

public:
	PrintFunction(Node* expr) 
		: printExpr_(expr) 
	{}
	~PrintFunction() { delete printExpr_; }
	int visit(IVisitor* vis) { return vis->visit(this); }
	Node* printExpr() { return printExpr_; }
};


class ReadFunction : public Node
{
	std::string varName_;
public:
	ReadFunction(std::string& name) 
		: varName_(name) 
	{}
	std::string& varName() { return varName_; }
	int visit(IVisitor* vis) { return vis->visit(this); }

};

#endif // IOFUNCTIONSNODE_H
