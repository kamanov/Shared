#ifndef LANGUAGEINFO_H
#define LANGUAGEINFO_H

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "token.h"

using std::string;
using std::vector;
using std::map;

struct LanguageInfo
{
	const string delimiters;
	const string operators;
	vector<string> comparisonOperators;
    	map<string, Token::TokenType> tocenDict_;


	LanguageInfo() 
		: delimiters(" ,:()\n\r\t")
		, operators("+-/*=><!")
	{
		comparisonOperators.resize(6);
		const char* compOperators[6] = {"==", "<", ">", "<=", ">=", "!="};
		std::copy(compOperators, compOperators + 6, comparisonOperators.begin());
		makeDict();
	}

	void makeDict() 
	{
				tocenDict_[":"] = Token::TCOLON;
				tocenDict_[")"] = Token::TRIGHTBRACKET;
				tocenDict_["("] = Token::TLEFTBRACKET;
				tocenDict_["+"] = Token::TADD;
				tocenDict_["="] = Token::TEQUAL;
				tocenDict_["-"] = Token::TSUB;
				tocenDict_["*"] = Token::TMUL;
				tocenDict_["/"] = Token::TDIV;
				tocenDict_["while"] = Token::TWHILE;
				tocenDict_["if"] = Token::TIF;
				tocenDict_["end"] = Token::TEND;
				tocenDict_["def"] = Token::TDEF;
				tocenDict_["return"] = Token::TRETURN;
				tocenDict_["print"] = Token::TPRINT;
				tocenDict_["read"] = Token::TREAD;
	}

};

#endif // LANGUAGEINFO_H
