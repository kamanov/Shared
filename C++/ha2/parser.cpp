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

	if(isUnaryOperation()){
		left = new Number(0);
	}
	else {
        	left = parseSummand();
	}

    	while ( checkType(Token::TSUB) || checkType(Token::TADD) ) {
        	processExpressionSummands(left);
	}
	return left;
}



Node* Parser::parseSummand()
{
	Node* left = parseFactor();
	while ( checkType(Token::TMUL) || checkType(Token::TDIV) ) {
        	processSummandFactors(left);
	}
	return left;
}

Node* Parser::parseFactor()
{
	if(checkType(Token::TNUMBER)) {
        	return parseNumber();
	}
   	else if(checkType(Token::TLEFTBRACKET) ) {
        	return parseNestedExpression();
	}
    	else if(checkType(Token::TVARIABLE)) {
		return parseVariable();
	}
	else {
		raiseSyntaxError();
		return 0;
	}

}

bool Parser::isUnaryOperation() const
{
	return checkType(Token::TSUB);
}

int Parser::tokenLine() const
{
	return currentToken_.getLine();
}

const std::string& Parser::tokenValue() const
{
	return currentToken_.getVal();
}

void Parser::processExpressionSummands(Node* &left)
{
	Arithmetic::Operation op;
	if(checkType(Token::TADD))
		op = Arithmetic::ADD;
	else
		op = Arithmetic::SUB;
	
	nextToken();
	Node* right = parseSummand();
	left = new Arithmetic(left, right, op);
}

void Parser::processSummandFactors(Node* &left)
{
	Arithmetic::Operation op;
	if(checkType(Token::TMUL))
		op = Arithmetic::MUL;
	else
        	op = Arithmetic::DIV;

    	int curLine = tokenLine();
   	nextToken();
    	Node* right = parseFactor();
    	left = new Arithmetic(left, right, op, curLine);
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
	std::string varName = tokenValue();
	nextToken();
    	assertType(Token::TEQUAL);
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
    	assertType(Token::TCOMPOPERATOR);
    	compOperation = tokenValue();
    	nextToken();

	Node* rval = parseExpresion();

	return new Condition(lval, rval, compOperation);
}

Node* Parser::parseControlStmt()
{
	Token::TokenType type = currentToken_.getType();
	nextToken();
	Node* condition = parseCondition();
    	assertType(Token::TCOLON);
    	nextToken();

	Body* body;
	if(isFunctionParsed_)
		body = parseBody(&Parser::haveNextFunctionStatement);
	else
		body = parseBody(&Parser::haveNextStatement);

    	assertType(Token::TEND);
    	nextToken();

    	return new ControlNode(condition, body, type);
}

Body* Parser::parseBody(bool (Parser::*stmtCondition)() const)
{
	Body* body = new Body();

    	while ((this->*stmtCondition)()) {
		Node* stmt = parseStatement();
		if(stmt != 0)
			body->addStatement(stmt);
	}

	return body;
}

bool Parser::haveNextStatement() const
{
	Token::TokenType validTypes[] = { 	Token::TVARIABLE,
                                      		Token::TPRINT,
                                      		Token::TREAD,
                                      		Token::TIF,
                                      		Token::TWHILE,
                                      		Token::TDEF
								};
    	bool result = false;
    	for(unsigned int i = 0; i < sizeof(validTypes)/sizeof(Token::TokenType); i++){
        	result = result || checkType(validTypes[i]);
    	}
    	return result;
}

bool Parser::haveNextFunctionStatement() const
{
	return (haveNextStatement() || checkType(Token::TRETURN)) && !checkType(Token::TDEF);
}

Node* Parser::parseStatement()
{
	switch(currentToken_.getType()) {
	case Token::TVARIABLE : 	return parseVariableStatement();
	case Token::TPRINT : 		return parsePrintFunction();
	case Token::TWHILE : 		return parseControlStmt();
	case Token::TIF : 		return parseControlStmt();
	case Token::TDEF : 		parseDefFunction();
					break;
	case Token::TRETURN : 		return parseReturn();
	case Token::TREAD : 		return parseReadFunction();
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

Node* Parser::parseVariable()
{
    	std::string varName = tokenValue();
    	int line = tokenLine();
    	nextToken();
    	if(checkType(Token::TLEFTBRACKET)) {
        	nextToken();
        	return parseCallFunction(varName);
    	}
    	else
        	return new Variable(varName, line);
}

void Parser::parseDefFunction()
{
	nextToken();

   	assertType(Token::TVARIABLE);
        const std::string fName = tokenValue();
    	nextToken();

	std::vector<std::string> formalParameters;
	parseFunctionParameters(formalParameters);

    	assertType(Token::TCOLON);
    	nextToken();

	isFunctionParsed_ = true;

	Body* functionBody = parseBody(&Parser::haveNextFunctionStatement);
	isFunctionParsed_ = false;
    	assertType(Token::TEND);
    	nextToken();

        functionTable_[fName] = FunctionInfo(formalParameters, functionBody);
}

void Parser::parseFunctionParameters(std::vector<std::string>& formalParameters)
{
	assertType(Token::TLEFTBRACKET);
	nextToken();


    	while(!checkType(Token::TRIGHTBRACKET)) {
        	assertType(Token::TVARIABLE);
        	formalParameters.push_back(currentToken_.getVal());
        	nextToken();

        	if(checkType(Token::TEOF))
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
	while(!checkType(Token::TRIGHTBRACKET)) {
		fParameters.push_back(parseExpresion());
        	if(checkType(Token::TEOF))
			raiseSyntaxError();
	}
	nextToken();
}

Node* Parser::parseProgram()
{
	Body* body = parseBody(&Parser::haveNextStatement);
    	assertType(Token::TEOF);
	return new Program(body);
}


const std::map<const std::string, FunctionInfo>& Parser::getFunctionTable() const
{ 
	return functionTable_; 
}


Node* Parser::parseReturn()
{
	nextToken();
	Node* expr = parseExpresion();
	return new ReturnNode(expr);

}

Node* Parser::parseNumber()
{
    	int value = std::stoi(tokenValue());
    	nextToken();
    	return new Number(value);
}

Node* Parser::parseNestedExpression()
{
    	nextToken();
    	Node* expr = parseExpresion();
    	assertType(Token::TRIGHTBRACKET);
    	nextToken();
    	return expr;
}

Node* Parser::parseReadFunction()
{
	nextToken();
	std::string varName;
    	assertType(Token::TVARIABLE);
    	varName = tokenValue();
    	nextToken();
	return new ReadFunction(varName);
}

void Parser::raiseSyntaxError() const
{
    	throw SyntaxException(tokenLine());
}

bool Parser::checkType(Token::TokenType type) const
{
    	return currentToken_.getType() == type;
}

void Parser::assertType(Token::TokenType type) const
{
    	if(!checkType(type))
        	raiseSyntaxError();
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
