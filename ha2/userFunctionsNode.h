#ifndef USERFUNCTIONSNODE_H
#define USERFUNCTIONSNODE_H


#include <vector>
#include <string>
#include "node.h"
#include "ivisitor.h"

class CallFunction : public Node
{
    	const std::string functionName_;
    	const std::vector<Node*> params_;
    	const int line_;
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
    	const std::vector<Node*>& parameters() const { return params_; }
    	const std::string& functionName() const { return functionName_; }
    	int line() const { return line_; }
    	int visit(IVisitor* vis) const { return vis->visit(this); }

};

class ReturnNode : public Node
{
    	Node* const expr_;
public:
	ReturnNode(Node* expr) 
		: expr_(expr) 
	{}
	~ReturnNode() {	delete expr_; }
   	Node* expr() const { return expr_; }
    	int visit(IVisitor* vis) const { return vis->visit(this); }

};



#endif // USERFUNCTIONSNODE_H






