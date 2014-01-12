#include <iostream>
#include "nodeheaders.h"
#include "evaluator.h"
#include "node.h"
#include "token.h"


Evaluator::Evaluator(const std::map<const std::string, FunctionInfo>& functionTable)
    : functionTable_(functionTable)
{
	scopeBlock globalScope;
	scopeVect_.push_back(globalScope);
	isReturned_ = false;
}


scopeBlock& Evaluator::currentScope()
{
	return scopeVect_.back();
}

int Evaluator::visit(const Arithmetic* node)
{
	int left = node->leftChild()->visit(this);
	int right = node->rightChild()->visit(this);
	switch(node->operation()) {
	case Arithmetic::ADD :return left + right;
	case Arithmetic::SUB : return left - right;
	case Arithmetic::MUL :return left * right;
	case Arithmetic::DIV :  if (right == 0) {
					std::string str("");
					raiseRunTimeError(node->line(), RunTimeException::DIVISIONZERO, str);
					return 0;

				}
				else
					return left / right;
	}
	return 0;
}

int Evaluator::visit(const Number* item)
{
	return item->value();
}

int Evaluator::visit(const VariableAssign* v)
{
	int varValue = v->child()->visit(this);
	scopeBlock& scope = currentScope();
	scope[v->name()] = varValue;
	return 0;
}

int Evaluator::visit(const Variable* fvar)
{
	scopeBlock& scope = currentScope();
	if(findVar(scope, fvar->name()))
		return scope[fvar->name()];
	else {
		raiseRunTimeError(fvar->line(), RunTimeException::UNDEFVAR, fvar->name());
		return 0;
	}
}

bool Evaluator::findVar(scopeBlock& outScope, const std::string& name)
{
	int size = scopeVect_.size();
	for(int i = size - 1; i >= 0; i--) {
		outScope = scopeVect_[i];
		if(outScope.find(name) != outScope.end())
			return true;			
	}
	return false;
}

int Evaluator::visit(const PrintFunction* pfunc)
{
	int result = pfunc->printExpr()->visit(this);
	std::cout << result << std::endl;
	return 0;

}

int Evaluator::visit(const Condition* node)
{
	int left = node->leftChild()->visit(this);
	int right = node->rightChild()->visit(this);
	return makeComparation(left, right, node->operation());
}

int Evaluator::makeComparation(int lval, int rval, const std::string& compOperation)
{

	if(compOperation == "==") {
		return lval == rval;
	}
	else if(compOperation == ">") {
		return lval > rval;
	}
	else if(compOperation == ">=") {
		return lval >= rval;
	}
	else if(compOperation == "<") {
		return lval < rval;
	}
	else if(compOperation == "<=") {
		return lval <= rval;
	}
	else {
		return lval != rval;
	}
}


int Evaluator::visit(const ControlNode* cnode)
{
	if(cnode->controlType() == Token::TWHILE)
		return processWhileControl(cnode);
	else if (cnode->controlType() == Token::TIF)
		return processIfControl(cnode);
	
	return 0;
}

int Evaluator::processWhileControl(const ControlNode* cnode)
{
	int result;
	while(cnode->condition()->visit(this)) {
		result = cnode->body()->visit(this);
		if(isReturned_)
			return result;
	}
	return 0;
}

int Evaluator::processIfControl(const ControlNode* cnode)
{
	if (cnode->condition()->visit(this)) {
		return cnode->body()->visit(this);
	}
	return 0;

}
int Evaluator::visit(const Body* body)
{
    const std::list<Node*>& stmts = body->stmtList();
	auto it = stmts.begin();
	while(it != stmts.end()) {
		int res = (*it)->visit(this);
		if(isReturned_)
			return res;
		++it;
	}
	return 0;
}


int Evaluator::visit(const Program* program)
{
	program->body()->visit(this);
	return 0;
}


int Evaluator::visit(const CallFunction* function)
{
    	const std::string& fName = function->functionName();
    	const std::vector<Node*>& params = function->parameters();
	if(functionTable_.find(fName) == functionTable_.end())
		raiseRunTimeError(function->line(), RunTimeException::UNDEFFUNC, fName);
    	if(params.size() != functionTable_.at(fName).functionParameters.size())
		raiseRunTimeError(function->line(), RunTimeException::ARGMISMATCH, fName);

	addFunctionScope(function);
	Body* body = functionTable_.at(fName).body;

	int result = body->visit(this);
	isReturned_ = false;

	removeFunctionScope();

	return result;
}

void Evaluator::addFunctionScope(const CallFunction* function)
{
    	const std::vector<Node*>& params = function->parameters();
	int size = params.size();
    	const std::vector<std::string>& varNames = functionTable_.at(function->functionName()).functionParameters;
	scopeBlock functionScope;
	for(int i = 0; i < size; i++) {
		int value = params[i]->visit(this);
		functionScope[varNames[i]] = value;
	}

	scopeVect_.push_back(functionScope);
}

void Evaluator::removeFunctionScope()
{
	scopeVect_.pop_back();
}

int Evaluator::visit(const ReturnNode* retn)
{
	Node* retExpr = retn->expr();
	int result = retExpr->visit(this);
	isReturned_ = true;
	return result;
}


int Evaluator::visit(const ReadFunction* rfunc)
{
	scopeBlock& scope = currentScope();
	int x;
	std::cin >> x;
	scope[rfunc->varName()] = x;
	return 0;

}

void Evaluator::raiseRunTimeError(int line, RunTimeException::ErrorType type, const std::string& varName) const
{
	throw RunTimeException(line, type, varName);
}
