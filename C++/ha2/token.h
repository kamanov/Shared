#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
public:
	enum TokenType { 
					TNUMBER,
					TVARIABLE,
					TCOMPOPERATOR,
					TCOLON,
					TLEFTBRACKET,
					TRIGHTBRACKET,
					TADD,
					TEQUAL,
					TSUB,
					TMUL,
					TDIV,
					TIF,
					TEND,
					TDEF,
					TWHILE,
					TRETURN,
					TPRINT,
					TREAD,
					TEOF,
					TUNKNOWN
	};

private:
    	TokenType type_;
    	std::string value_;
    	int tokenLine_;

public:
	Token(std::string& value, TokenType type, int line) : type_(type), value_(value), tokenLine_(line) {}
	Token() : type_(TUNKNOWN) {} 
    	const std::string& getVal() const{ return value_; }
    	TokenType getType() const { return type_; }
    	int getLine() const { return tokenLine_; }
    	void setVal(const std::string& value) { value_ = value; }
    	void setType(const TokenType type) { type_ = type; }
    	void setLine(const int line) { tokenLine_ = line; }
	
};


#endif // TOKEN_H
