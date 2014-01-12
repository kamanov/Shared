#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include <string>
#include "node.h"
#include "ivisitor.h"


class VariableAssign : public Node
{
    	const std::string id_;
    	Node* const child_;
public:
	VariableAssign(std::string& varname, Node* child) 
		: id_(varname)
		, child_(child) 
	{}
	~VariableAssign() { delete child_; }
    	Node* child() const { return child_; }
    	const std::string& name() const { return id_; }
    	int visit(IVisitor* vis) const { return vis->visit(this); }
};


class Variable : public Node
{
    	const std::string id_;
    	const int line_;
public:
	Variable(std::string& varName, int line) 
		: id_(varName)
		, line_(line) 
	{}
    	const std::string& name() const { return id_; }
    	int line() const { return line_; }
    	int visit(IVisitor* vis) const { return vis->visit(this); }
};

#endif // VARIABLENODE_H
