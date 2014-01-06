#include <memory>
#include "interpreter.h"
#include "node.h"
#include "parser.h"
#include "lexer.h"
#include "evaluator.h"

Interpreter::Interpreter()
	: lexer_(new Lexer(languageInfo_))
	, parser_(0)
	, evaluator_(0)
{

}
	
void Interpreter::startInterpretation(std::ifstream& inputStream)
{
	std::string programText;
	readInputFile(inputStream, programText);

	lexer_->startLexAnalyze(programText);

	parser_ = new Parser(lexer_->getTokenBuffer());
	parser_->startParsing();

	executeProgram();
}

void Interpreter::executeProgram()
{
	evaluator_ = new Evaluator(parser_->getFunctionTable());
	std::unique_ptr<Node> parseTreeRoot = parser_->getParseTree();
	parseTreeRoot->visit(evaluator_); 
}

void Interpreter::readInputFile(std::ifstream& inputStream, std::string& outString)
{
	int length = getFileLength(inputStream);
	outString.resize(length);
	inputStream.read(&outString[0], length);
}

int Interpreter::getFileLength(std::ifstream& inputStream)
{
	inputStream.seekg (0, inputStream.end);
	int length = inputStream.tellg();
	inputStream.seekg (0, inputStream.beg);
	return length;
}

Interpreter::~Interpreter()
{
	delete lexer_;
	if(parser_ != 0)
		delete parser_;
	if(evaluator_ != 0)
		delete evaluator_;
}
