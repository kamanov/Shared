#ifndef IVISITOR_H
#define IVISITOR_H

class Arithmetic;
class Number;
class VariableAssign;
class Variable;
class PrintFunction;
class Condition;
class ControlNode;
class Body;
class Program;
class CallFunction;
class ReturnNode;
class ReadFunction;

class IVisitor 
{
  public:
    	virtual int visit(const Arithmetic* op) = 0;
    	virtual int visit(const Number* n) = 0;
    	virtual int visit(const VariableAssign* v) = 0;
    	virtual int visit(const Variable* n) = 0;
    	virtual int visit(const PrintFunction* pfunc) = 0;
    	virtual int visit(const Condition* op) = 0;
    	virtual int visit(const ControlNode* cnode) = 0;
    	virtual int visit(const Body* body) = 0;
    	virtual int visit(const Program* program) = 0;
    	virtual int visit(const CallFunction* program) = 0;
    	virtual int visit(const ReturnNode* retn) = 0;
    	virtual int visit(const ReadFunction* rfunc) = 0;
};

#endif // IVISITOR_H
