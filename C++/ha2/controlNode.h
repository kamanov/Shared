#ifndef CONTROLNODE_H
#define CONTROLNODE_H

#include "token.h"
#include "node.h"
#include "ivisitor.h"


class ControlNode : public Node
{
    	Node* const condition_;
    	Node* const body_;
    	const Token::TokenType controlType_;
public:
	ControlNode(Node* condition, Node* body, Token::TokenType type) 
		: condition_(condition)
		, body_(body)
		, controlType_(type) 
	{}
	~ControlNode() { delete condition_; delete body_; }
    	Node* condition() const { return condition_; }
    	Node* body() const { return body_; }
    	Token::TokenType controlType() const { return controlType_; }
    	int visit(IVisitor* vis) const { return vis->visit(this); }

};

#endif // CONTROLNODE_H
