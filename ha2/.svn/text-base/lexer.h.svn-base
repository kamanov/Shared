#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include "token.h"
#include "languageInfo.h"

class Lexer
{
	std::vector<Token> tokenBuffer_;
    	const LanguageInfo& languageInfo_;
    	std::string delims_;
	unsigned int offset_;
    	bool getToken(const std::string& text, Token& token);
    	void checkCompoundStatement(unsigned int& position, const std::string& text);
    	bool skipSpaces(const std::string& text);
    	bool skipComments(const std::string& text);
    	bool defTokenValue(const std::string& text, std::string& value);
    	void defTokenType(Token& token, const std::string& value);
    	bool checkIsNumber(const std::string& value);
    	void verifyVariableName(const std::string& name);
	int lineCount_;
    	void raiseSyntaxError() const;
    	void lineCountProcess(const std::string& text);

public:

    	Lexer(const LanguageInfo& linfo);
	virtual ~Lexer() {}
	void startLexAnalyze(std::string& text);
    	void printTokenBuffer() const;
	std::vector<Token>& getTokenBuffer() { return tokenBuffer_; }
};

#endif // LEXER_H
