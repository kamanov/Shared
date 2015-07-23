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
    	std::vector<Token>::const_iterator itToken_;
    	std::map<const std::string, FunctionInfo> functionTable_;
	void parseFunctionParameters(std::vector<std::string>& formalParameters);
	void parseFunctionParameters(std::vector<Node*>& fParameters);
    	bool haveNextStatement() const;
    	bool haveNextFunctionStatement() const;
	void nextToken();
	bool isFunctionParsed_;
	Token getNextToken();
    	void raiseSyntaxError() const;
    	bool checkType(Token::TokenType type) const;
    	void assertType(Token::TokenType type) const;
        bool isUnaryOperation() const;
        int tokenLine() const;
        const std::string& tokenValue() const;
    	void processExpressionSummands(Node*& left);
    	void processSummandFactors(Node*& left);
	Node* parseTreeRoot_;
	Node* parseExpresion();
    	Node* parseSummand();
	Node* parseFactor();
	Node* parseVarAssign();
	Node* parsePrintFunction();
	Node* parseCondition();
	Node* parseControlStmt();
	Node* parseStatement();
	Node* parseProgram();
	Node* parseIfStatement();
	Node* parseReturn();
    	Node* parseNumber();
    	Node* parseNestedExpression();
	Node* parseVariableStatement();
    	Node* parseVariable();
	Node* parseReadFunction();
	void parseDefFunction();
	Node* parseCallFunction(std::string& functionName);
        Body* parseBody(bool (Parser::*stmtCondition)() const);

public:
	
	Parser(std::vector<Token>& tokenBuffer);
	virtual ~Parser();
   	const std::map<const std::string, FunctionInfo>& getFunctionTable() const;
	void startParsing();
    	std::unique_ptr<Node> getParseTree();
};



#endif //PARSER_H
