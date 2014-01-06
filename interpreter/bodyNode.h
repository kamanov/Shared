#ifndef BODYNODE_H
#define BODYNODE_H

#include <list>
#include "node.h"
#include "ivisitor.h"

class Body : public Node
{
	std::list<Node*> stmtList_;
public:
	~Body() { 
		auto it = stmtList_.begin(); 
		while(it != stmtList_.end()) {
			delete (*it);
			++it;
		}
	}
	std::list<Node*>& stmtList() { return stmtList_; }
	void addStatement(Node* stmt) { stmtList_.push_back(stmt); }
	int visit(IVisitor* vis) { return vis->visit(this); }
};

#endif // BODYNODE_H
