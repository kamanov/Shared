#ifndef USERFUNCTIONSNODE_H
#define USERFUNCTIONSNODE_H


#include <vector>
#include <string>
#include "node.h"
#include "ivisitor.h"

class CallFunction : public Node
{
	std::string functionName_;	
	std::vector<Node*> params_;
	int line_;
public:
	CallFunction(std::string& functionName, std::vector<Node*>& params, int line) 
		: functionName_(functionName)
		, params_(params)
		, line_(line) 
	{}
	~CallFunction() { 
		auto it = params_.begin(); 
		while(it != params_.end()) {
			delete (*it);
			++it;
		}
	
	}
	std::vector<Node*>& parameters() { return params_; }
	std::string& functionName() { return functionName_; }
	int line() { return line_; }
	int visit(IVisitor* vis) { return vis->visit(this); }

};

class ReturnNode : public Node
{
	Node* expr_;
public:
	ReturnNode(Node* expr) 
		: expr_(expr) 
	{}
	~ReturnNode() {	delete expr_; }
	Node* expr() { return expr_; }
	int visit(IVisitor* vis) { return vis->visit(this); }

};



#endif // USERFUNCTIONSNODE_H






