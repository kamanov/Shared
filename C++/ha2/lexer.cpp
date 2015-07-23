#include <iostream>
#include <algorithm>
#include "lexer.h"
#include "exceptions.h"
#include <sstream>
#include <cstring>
using std::find;


Lexer::Lexer(const LanguageInfo& linfo)
	: languageInfo_(linfo)
	, offset_(0)
	, lineCount_(1)
{
}


bool Lexer::getToken(const std::string& text, Token& token)
{
	if(!skipSpaces(text))
		return false;
	if(!skipComments(text))
		return false;
	
	std::string value;
	if(!defTokenValue(text, value))
		return false;

	defTokenType(token, value);
	token.setLine(lineCount_);
	return true;

}

void Lexer::checkCompoundStatement(unsigned int& position, const std::string& text)
{
	std::string firstCharOfStatement = "=!><";
	if(position != text.length() - 1) {
		if (text[position + 1] == '=') {
			if (firstCharOfStatement.find(text[position]) != std::string::npos)
				position++;
		}
	}

}


bool Lexer::skipSpaces(const std::string& text)
{
	if(strchr(" \t\r\n",text[offset_])) {
		offset_ = text.find_first_not_of(" \t\r", offset_);
		lineCountProcess(text);
		if(offset_ == std::string::npos) {
			offset_ = text.length();
			return false;
		}
	}
	return true;
}

void Lexer::lineCountProcess(const std::string& text)
{
	if( offset_ == std::string::npos)
		return;

	while(offset_ < text.length() && text[offset_] == '\n')
    	{
        	lineCount_++;
        	offset_++;
        	offset_ = text.find_first_not_of(" \t\r", offset_);
        	if(offset_ == std::string::npos)
            		break;
    	}
}

bool Lexer::skipComments(const std::string& text)
{
	if(text[offset_] == '#') {
		unsigned int pos = text.find_first_of("\n", offset_);
		if(pos == std::string::npos) {
			offset_ = text.length();
			return false;
		}
		else {
			lineCount_++;
			offset_ = pos + 1;
			skipSpaces(text);
		}
	}
	return true;

}

bool Lexer::defTokenValue(const std::string& text, std::string& value)
{
	if(offset_ == text.size())
		return false;
	unsigned int nextPos = text.find_first_of(delims_, offset_);

	if(nextPos == std::string::npos) {
		value = text.substr(offset_);
		offset_ = text.length();
	}
	else {

		if(nextPos == offset_) {
			checkCompoundStatement(nextPos, text);
			if(text[offset_] == ',') {
				offset_++;
				return false;
			}
			nextPos++;
		}

		value = text.substr(offset_, nextPos - offset_);
		offset_ = nextPos;
	}
	return true;
}

void Lexer::defTokenType(Token& token, const std::string& value)
{
    	const std::vector<std::string>& compOperations = languageInfo_.comparisonOperators;
    	const map<string, Token::TokenType>& tocenDict = languageInfo_.tocenDict_; 
	

	if(tocenDict.find(value) != tocenDict.end()) {
        token.setType(tocenDict.at(value));
	}
	else if(find(compOperations.begin(), compOperations.end(), value) != compOperations.end()) {
		token.setType(Token::TCOMPOPERATOR);
		token.setVal(value);
	}
	else if (checkIsNumber(value)) {
		token.setType(Token::TNUMBER);
		token.setVal(value);
	}
	else {
		token.setType(Token::TVARIABLE);
		verifyVariableName(value);
		token.setVal(value);

	}

}

bool Lexer::checkIsNumber(const std::string& value)
{
	int length = value.size();

	for(int i = 0; i < length; i++) {
		if(!isdigit(value[i]))
			return false;
	}
	return true;
}

void Lexer::verifyVariableName(const std::string& name)
{
	bool isValid = true;

	int length = name.size();
	for(int i = 0; i < length; i++) {
		if (! (isalnum(name[i]) || name[i] == '_' ) )
			isValid = false;
	}
	
	if(isdigit(name[0]))
		isValid = false;

	if(!isValid) {
		raiseSyntaxError();
	}
}

void Lexer::startLexAnalyze(std::string& text)
{
	delims_ = languageInfo_.delimiters + languageInfo_.operators;
	unsigned int textLength = text.size();

	while( offset_ != textLength) {

		Token token;
		if(getToken(text, token))
			tokenBuffer_.push_back(token);

	}
	std::string str("EOF");
	Token EOFtoken(str, Token::TEOF, lineCount_);
	tokenBuffer_.push_back(EOFtoken);

}


void Lexer::printTokenBuffer() const
{
	auto it = tokenBuffer_.begin();
	string tokenTypes[] = { "TNUMBER",
				"TVARIABLE",
				"TCOMPOPERATOR",
				"TCOLON",
				"TLEFTBRACKET",
				"TRIGHTBRACKET",
				"TADD",
				"TEQUAL",
				"TSUB",
				"TMUL",
				"TDIV",
				"TIF",
				"TEND",
				"TDEF",
				"TWHILE",
				"TRETURN",
				"TPRINT",
				"TREAD",
				"TEOF",
				"TUNKNOWN"
};

	while(it != tokenBuffer_.end()) {
		std::cout << tokenTypes[(*it).getType()] << " " << (*it).getVal() << " " << (*it).getLine() << std::endl;
		++it;
	}

}

void Lexer::raiseSyntaxError() const
{
	throw SyntaxException(lineCount_);
}
