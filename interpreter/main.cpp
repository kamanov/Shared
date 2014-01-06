#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "interpreter.h"

int main(int argc, char* argv[])
{
	try {
		if (argc < 2)
			throw std::invalid_argument("Expected input file name");
		
		const char* filename = argv[1];

		std::ifstream input;
		input.open(filename, std::ifstream::binary);
		
		Interpreter interpreter;
		interpreter.startInterpretation(input);	
	}
	catch(std::exception& exception) {
		std::cerr << exception.what() << std::endl;
	}


	return 0;
}
