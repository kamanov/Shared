#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <fstream>
#include"languageInfo.h"
class Parser;
class Lexer;
class Evaluator;

class Interpreter
{
	LanguageInfo languageInfo_;
	Lexer* lexer_;
	Parser* parser_;
	Evaluator* evaluator_;
	int getFileLength(std::ifstream& inputStream);
	void readInputFile(std::ifstream& inputStream, std::string& outString);
	void executeProgram();
public:
	Interpreter();
	~Interpreter();
	void startInterpretation(std::ifstream& inputStream);
};

#endif // INTERPRETER_H
