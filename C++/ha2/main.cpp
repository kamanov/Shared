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
		input.open(filename, std::ios_base::in | std::ifstream::binary);
		input.exceptions(std::ifstream::failbit | std::ifstream::badbit);		
		Interpreter interpreter;
		interpreter.startInterpretation(input);	
	}
	catch (std::ios_base::failure e) {
                std::cerr << "Exception opening/closing input file" << std::endl;
        }
        catch(std::exception& exception) {
                std::cerr << exception.what() << std::endl;
        }


	return 0;
}
