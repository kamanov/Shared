#include "parser.h"
#include "token.h"
#include "exceptions.h"
#include "nodeheaders.h"

Parser::Parser(std::vector<Token>& tokenBuffer)
	: tokenBuffer_(tokenBuffer)
	, currentToken_(tokenBuffer_[0])
	, itToken_(tokenBuffer_.begin())
	, isFunctionParsed_(false)
	, parseTreeRoot_(0)
{
}


Node* Parser::parseExpresion()
{
	Node* left;
	if(currentToken_.getType() == Token::TSUB){
		left = new Number(0);
	}
	else {
		left = parseItem();
	}
	while (currentToken_.getType() == Token::TSUB || currentToken_.getType() == Token::TADD) {
		
		Arithmetic::Operation op;
		if(currentToken_.getType() == Token::TADD)
			op = Arithmetic::ADD;
		else
			op = Arithmetic::SUB;
		nextToken();
		Node* right = parseItem();
		left = new Arithmetic(left, right, op);
	}
	return left;
}

Node* Parser::parseItem()
{
	Node* left = parseFactor();
	while (currentToken_.getType() == Token::TMUL || currentToken_.getType() == Token::TDIV) {
		
		Arithmetic::Operation op;
		if(currentToken_.getType() == Token::TMUL)
			op = Arithmetic::MUL;
		else
			op = Arithmetic::DIV;
		int line = currentToken_.getLine();
		nextToken();
		Node* right = parseFactor();
		left = new Arithmetic(left, right, op, line);
	}
	return left;

}

Node* Parser::parseFactor()
{

	if(currentToken_.getType() == Token::TNUMBER) {
		int value = std::stoi(currentToken_.getVal());
		nextToken();
		return new Number(value);		
	}
	else if(currentToken_.getType() == Token::TLEFTBRACKET ) {
		nextToken();
		Node* expr = parseExpresion();
		if(currentToken_.getType() == Token::TRIGHTBRACKET)
			nextToken();
		else
			raiseSyntaxError();
		return expr;
		
	}
	else if(currentToken_.getType() == Token::TVARIABLE) {
		std::string varName = currentToken_.getVal();
		int line = currentToken_.getLine();
		nextToken();
		if(currentToken_.getType() == Token::TLEFTBRACKET) {
			nextToken();
			return parseCallFunction(varName);
		}
		else
			return new Variable(varName, line);
	}
	else {
		raiseSyntaxError();
		return 0;
	}

}

void Parser::nextToken()
{
	if(itToken_ != tokenBuffer_.end() - 1) {
		++itToken_;
		currentToken_ = *itToken_;
	}
}

Token Parser::getNextToken() {
	auto it = itToken_;
	++it;
	return *it;
}

Node* Parser::parseVarAssign()
{
	std::string varName = currentToken_.getVal();
	nextToken();
	if(currentToken_.getType() != Token::TEQUAL)
		raiseSyntaxError();
	else
		nextToken();

	Node* value = parseExpresion();
	return new VariableAssign(varName, value);

}


Node* Parser::parsePrintFunction()
{
	nextToken();
	Node* valToPrint = parseExpresion();
	return new PrintFunction(valToPrint);
}

Node* Parser::parseCondition()
{
	Node* lval = parseExpresion();
	std::string compOperation;
	if(currentToken_.getType() == Token::TCOMPOPERATOR) {
		compOperation = currentToken_.getVal();
		nextToken();
	}
	else 
		raiseSyntaxError();

	Node* rval = parseExpresion();

	return new Condition(lval, rval, compOperation);
}

Node* Parser::parseControlStmt()
{
	Token::TokenType type = currentToken_.getType();
	nextToken();
	Node* condition = parseCondition();
	if(currentToken_.getType() == Token::TCOLON)
		nextToken();
	else 
		raiseSyntaxError();

	Body* body;
	if(isFunctionParsed_)
		body = parseBody(&Parser::haveNextFunctionStatement);
	else
		body = parseBody(&Parser::haveNextStatement);
	if(currentToken_.getType() == Token::TEND)
		nextToken();
	else 
		raiseSyntaxError();

		return new ControlNode(condition, body, type);
}

Body* Parser::parseBody(bool (Parser::*cond)())
{
	Body* body = new Body();
	while ((this->*cond)()) {
		Node* stmt = parseStatement();
		if(stmt != 0)
			body->addStatement(stmt);
	}
	return body;

}

bool Parser::haveNextStatement()
{
	Token::TokenType type = currentToken_.getType();
	return (type == Token::TVARIABLE || type == Token::TPRINT || type == Token::TREAD || type == Token::TIF || type == Token::TWHILE || type == Token::TDEF);
}

bool Parser::haveNextFunctionStatement() 
{
	Token::TokenType type = currentToken_.getType();
	return (type == Token::TVARIABLE || type == Token::TPRINT || type == Token::TREAD || type == Token::TIF || type == Token::TWHILE || type == Token::TRETURN);
}

Node* Parser::parseStatement()
{
	switch(currentToken_.getType()) {
	case Token::TVARIABLE : return parseVariableStatement();
	case Token::TPRINT : return parsePrintFunction();
	case Token::TWHILE : return parseControlStmt();
	case Token::TIF : return parseControlStmt();
	case Token::TDEF : parseDefFunction();
						break;
	case Token::TRETURN : return parseReturn();
	case Token::TREAD : return parseReadFunction();
	default: break;
	}
	return 0;

}

Node* Parser::parseVariableStatement() 
{
	if(getNextToken().getType() == Token::TEQUAL)
		return parseVarAssign();
	else
		return parseExpresion();
}

void Parser::parseDefFunction()
{
	nextToken();

	std::string fName;
	if(currentToken_.getType() == Token::TVARIABLE){
		fName = currentToken_.getVal();
		nextToken();
	}
	else
		raiseSyntaxError();
	
	std::vector<std::string> formalParameters;
	parseFunctionParameters(formalParameters);

	if(currentToken_.getType() == Token::TCOLON) {
		nextToken();
	}
	else
		raiseSyntaxError();
	isFunctionParsed_ = true;
	Body* functionBody = parseBody(&Parser::haveNextFunctionStatement);
	isFunctionParsed_ = false;
	if(currentToken_.getType() == Token::TEND)
		nextToken();
	else 
		raiseSyntaxError();

	functionTable_[fName] = FunctionInfo(formalParameters, functionBody);

}

void Parser::parseFunctionParameters(std::vector<std::string>& formalParameters)
{
	if(currentToken_.getType() == Token::TLEFTBRACKET)
		nextToken();
	else
		raiseSyntaxError();

	while(currentToken_.getType() != Token::TRIGHTBRACKET) {
		if(currentToken_.getType() == Token::TVARIABLE) {
			formalParameters.push_back(currentToken_.getVal());
			nextToken();
		}
		else 
			raiseSyntaxError();
		if(currentToken_.getType() == Token::TEOF)
			raiseSyntaxError();

	}
	nextToken();
}


Node* Parser::parseCallFunction(std::string& functionName)
{
	int line = currentToken_.getLine();
	std::vector<Node*> fParamaters;
	parseFunctionParameters(fParamaters);
	return new CallFunction(functionName, fParamaters, line);

}

void Parser::parseFunctionParameters(std::vector<Node*>& fParameters)
{
	while(currentToken_.getType() != Token::TRIGHTBRACKET) {
		fParameters.push_back(parseExpresion());
		if(currentToken_.getType() == Token::TEOF)
			raiseSyntaxError();
	}
	nextToken();
}

Node* Parser::parseProgram()
{
	Body* body = parseBody(&Parser::haveNextStatement);
	if(currentToken_.getType() != Token::TEOF) 
		raiseSyntaxError();

	return new Program(body);
}



std::map<std::string, FunctionInfo>& Parser::getFunctionTable() 
{ 
	return functionTable_; 
}


Node* Parser::parseReturn()
{
	nextToken();
	Node* expr = parseExpresion();
	return new ReturnNode(expr);

}

Node* Parser::parseReadFunction()
{
	nextToken();
	std::string varName;
	if(currentToken_.getType() == Token::TVARIABLE) {
		varName = currentToken_.getVal();
		nextToken();
	}
	else 
		raiseSyntaxError();
	return new ReadFunction(varName);
}

void Parser::raiseSyntaxError()
{
	throw SyntaxException(currentToken_.getLine());
}

void Parser::startParsing()
{
	parseTreeRoot_ = parseProgram();
}

std::unique_ptr<Node> Parser::getParseTree()
{
	return std::unique_ptr<Node>(parseTreeRoot_);
}

Parser::~Parser()
{
	auto it = functionTable_.begin();
	while( it != functionTable_.end()) {
		Node* functionBody = (*it).second.body;
		if(functionBody != 0)
			delete functionBody;
		++it;
	}
}
