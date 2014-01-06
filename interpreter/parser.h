#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <map>
#include <vector>
#include "FunctionInfo.h"
#include "token.h"

class Node;
class Body;

class Parser
{
	std::vector<Token>& tokenBuffer_;
	Token& currentToken_;
	std::vector<Token>::iterator itToken_;
	std::map<std::string, FunctionInfo> functionTable_;
	void parseFunctionParameters(std::vector<std::string>& formalParameters);
	void parseFunctionParameters(std::vector<Node*>& fParameters);
	bool haveNextStatement();
	bool haveNextFunctionStatement(); 
	void nextToken();
	bool isFunctionParsed_;
	Token getNextToken();
	void raiseSyntaxError();
	
	Node* parseTreeRoot_;
	Node* parseExpresion();
	Node* parseItem();
	Node* parseFactor();
	Node* parseVarAssign();
	Node* parsePrintFunction();
	Node* parseCondition();
	Node* parseControlStmt();
	Node* parseStatement();
	Node* parseProgram();
	Node* parseIfStatement();
	Node* parseReturn();
	Node* parseVariableStatement();
	Node* parseReadFunction();
	void parseDefFunction();
	Node* parseCallFunction(std::string& functionName);
	Body* parseBody(bool (Parser::*cond)());

public:
	
	Parser(std::vector<Token>& tokenBuffer);
	~Parser();
	std::map<std::string, FunctionInfo>& getFunctionTable();
	void startParsing();
	std::unique_ptr<Node> getParseTree();
};



#endif //PARSER_H
