#ifndef CONTROLNODE_H
#define CONTROLNODE_H

#include "token.h"
#include "node.h"
#include "ivisitor.h"


class ControlNode : public Node
{
	Node* condition_;
	Node* body_;
	Token::TokenType controlType_;
public:
	ControlNode(Node* condition, Node* body, Token::TokenType type) 
		: condition_(condition)
		, body_(body)
		, controlType_(type) 
	{}
	~ControlNode() { delete condition_; delete body_; }
	Node* condition() { return condition_; }
	Node* body() { return body_; }
	Token::TokenType controlType() { return controlType_; }
	int visit(IVisitor* vis) { return vis->visit(this); }

};

#endif // CONTROLNODE_H
