#ifndef FUNCTIONINFO_H
#define FUNCTIONINFO_H

#include <vector>
class Body;

struct FunctionInfo
{
	std::vector<std::string> functionParameters;
    	Body* body;
	FunctionInfo(std::vector<std::string>& fParameters, Body* b)
		: functionParameters(fParameters)
		, body(b)
	{}
	FunctionInfo() 
		: body(0) 
	{}

};



#endif // FUNCTIONINFO_H
