#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include <string>
#include "node.h"
#include "ivisitor.h"


class VariableAssign : public Node
{
	std::string id_;
	Node* child_;
public:
	VariableAssign(std::string& varname, Node* child) 
		: id_(varname)
		, child_(child) 
	{}
	~VariableAssign() { delete child_; }
	Node* child() { return child_; }
	std::string& name() { return id_; }
	int visit(IVisitor* vis) { return vis->visit(this); }
};


class Variable : public Node
{
	std::string id_;
	int line_;
public:
	Variable(std::string& varName, int line) 
		: id_(varName)
		, line_(line) 
	{}
	std::string& name() { return id_; }
	int line() { return line_; }
	int visit(IVisitor* vis) { return vis->visit(this); }
};

#endif // VARIABLENODE_H
