#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <sstream>
#include <stdexcept>


class RunTimeException: public std::runtime_error
{
public:
	enum ErrorType{UNDEFVAR, UNDEFFUNC, DIVISIONZERO, ARGMISMATCH, COUNT};
    	RunTimeException(int line, ErrorType type, std::string name)
		: std::runtime_error("")
	{
		const char* erTypes[COUNT];
		erTypes[UNDEFVAR] = "undefined variable";
		erTypes[UNDEFFUNC] = "undefined function";
		erTypes[DIVISIONZERO] = "division by zero";
		erTypes[ARGMISMATCH] = "arguments number mismatch for";

		std::stringstream ss;
		ss << "Runtime error (line " << line << "): " << erTypes[type];
		if(type != DIVISIONZERO)
			ss << " '" << name << "'";


		 static_cast<std::runtime_error&>(*this) = std::runtime_error(ss.str());
	}

};


class SyntaxException: public std::logic_error
{
public:
	
    	SyntaxException(int line)
		: logic_error("")
	{
		std::stringstream ss;
		ss << "line " << line << ": syntax error"; 
		static_cast<std::logic_error&>(*this) = std::logic_error(ss.str()); 
	}
};

#endif //EXCEPTIONS_H
