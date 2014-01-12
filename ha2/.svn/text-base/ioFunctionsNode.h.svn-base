#ifndef IOFUNCTIONSNODE_H
#define IOFUNCTIONSNODE_H

#include "node.h"
#include "ivisitor.h"


class PrintFunction : public Node
{
    	Node* const printExpr_;

public:
	PrintFunction(Node* expr) 
		: printExpr_(expr) 
	{}
	~PrintFunction() { delete printExpr_; }
    	int visit(IVisitor* vis) const { return vis->visit(this); }
    	Node* printExpr() const { return printExpr_; }
};


class ReadFunction : public Node
{
    	const std::string varName_;
public:
	ReadFunction(std::string& name) 
		: varName_(name) 
	{}
    	const std::string& varName() const { return varName_; }
    	int visit(IVisitor* vis) const{ return vis->visit(this); }

};

#endif // IOFUNCTIONSNODE_H
