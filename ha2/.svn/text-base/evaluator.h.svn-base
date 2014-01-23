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
    	const std::map<const std::string, FunctionInfo>& functionTable_;//ssylka
    	int makeComparation(int lval, int rval, const std::string& compOperation);
    	int processWhileControl(const ControlNode* cnode);
    	int processIfControl(const ControlNode* cnode);
    	bool findVar(scopeBlock& outScope, const std::string& name);
    	void raiseRunTimeError(int line, RunTimeException::ErrorType type, const std::string& varName) const;
	scopeBlock& currentScope();
    	void addFunctionScope(const CallFunction* function);
	void removeFunctionScope();
    	int visit(const Arithmetic* node);
    	int visit(const Number* node);
    	int visit(const VariableAssign* v);
    	int visit(const Variable* fvar);
    	int visit(const PrintFunction* pfunc);
    	int visit(const Condition* node);
    	int visit(const ControlNode* cnode);
    	int visit(const Body* body);
    	int visit(const Program* program);
    	int visit(const CallFunction* function);
    	int visit(const ReturnNode* retn);
    	int visit(const ReadFunction* rfunc);
public:
    	Evaluator(const std::map<const std::string, FunctionInfo>& functionTable);
	virtual ~Evaluator() {}
};



#endif //EVALUATOR_H




