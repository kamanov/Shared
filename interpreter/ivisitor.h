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
	virtual int visit(Arithmetic* op) = 0;
	virtual int visit(Number* n) = 0;
	virtual int visit(VariableAssign* v) = 0;
	virtual int visit(Variable* n) = 0;
	virtual int visit(PrintFunction* pfunc) = 0;
	virtual int visit(Condition* op) = 0;
	virtual int visit(ControlNode* cnode) = 0;
	virtual int visit(Body* body) = 0;
	virtual int visit(Program* program) = 0;
	virtual int visit(CallFunction* program) = 0;
	virtual int visit(ReturnNode* retn) = 0;
	virtual int visit(ReadFunction* rfunc) = 0;
};

#endif // IVISITOR_H