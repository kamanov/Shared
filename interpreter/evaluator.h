#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <map>
#include <vector>
#include "FunctionInfo.h"
#include "exceptions.h"
#include "ivisitor.h"


typedef std::map<std::string, int> scopeBlock;

class Evaluator : public IVisitor
{
	bool isReturned_;
	std::vector<scopeBlock> scopeVect_;
	std::map<std::string, FunctionInfo>& functionTable_;
	int makeComparation(int lval, int rval, std::string& compOperation);
	int processWhileControl(ControlNode* cnode);
	int processIfControl(ControlNode* cnode);
	bool findVar(scopeBlock& outScope, std::string& name);
	void raiseRunTimeError(int line, RunTimeException::ErrorType type, std::string& varName);
	scopeBlock& currentScope();
	void addFunctionScope(CallFunction* function);
	void removeFunctionScope();
	int visit(Arithmetic* node);
	int visit(Number* node);
	int visit(VariableAssign* v);
	int visit(Variable* fvar);
	int visit(PrintFunction* pfunc);
	int visit(Condition* node);
	int visit(ControlNode* cnode);
	int visit(Body* body);
	int visit(Program* program);
	int visit(CallFunction* function);
	int visit(ReturnNode* retn);
	int visit(ReadFunction* rfunc);
public:
	Evaluator(std::map<std::string, FunctionInfo>& functionTable);
};



#endif //EVALUATOR_H




