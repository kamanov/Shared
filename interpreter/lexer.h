#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include "token.h"
#include "languageInfo.h"

class Lexer
{
	std::vector<Token> tokenBuffer_;
	LanguageInfo& languageInfo_;
	std::string delims_;
	unsigned int offset_;
	bool getToken(std::string& text, Token& token);
	void checkCompoundStatement(unsigned int& position, std::string& text);
	bool skipSpaces(std::string& text);
	bool skipComments(std::string& text);
	bool defTokenValue(std::string& text, std::string& value);
	void defTokenType(Token& token, std::string& value);
	bool checkIsNumber(std::string& value);
	void verifyVariableName(std::string& name);
	int lineCount_;
	void raiseSyntaxError();

public:

	Lexer(LanguageInfo& linfo);
	void startLexAnalyze(std::string& text);
	void printTokenBuffer();
	std::vector<Token>& getTokenBuffer() { return tokenBuffer_; }
};

#endif // LEXER_H