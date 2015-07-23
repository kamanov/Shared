#include <cstring>
#include <fstream>
#include "huffmancoder.h"
#include "huffmandecoder.h"
#include <ctime>

bool isFileEmpty(std::ifstream& input)
{
    input.seekg(0, input.end);
    int length = input.tellg();
    input.seekg(0, input.beg);

    return (length == 0);
}


int main(int argc, char *argv[])
{
	unsigned int st = clock();
	enum ACTION { COMPRESS, DECOMPRESS };

	ACTION action;

	const char* input_file;
	const char* output_file;
	for(int i=0; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0)
			input_file = argv[i + 1];
		if (strcmp(argv[i], "-o") == 0)
			output_file = argv[i + 1];
		if (strcmp(argv[i], "-c") == 0)
			action = COMPRESS;
		if (strcmp(argv[i], "-d") == 0)
			action = DECOMPRESS;
	}

	std::ifstream input;
	input.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::ofstream output;
	output.exceptions(std::ifstream::failbit | std::ifstream::badbit);


	try {
		input.open(input_file, std::ios_base::in | std::ios_base::binary);

        	if (isFileEmpty(input)) {
           		std::cout << "Input file is empty" << std::endl;
            		return 0;
       		}	
		
		output.open(output_file, std::ios_base::out | std::ios_base::binary);
	
	
		if (action == COMPRESS) {
			HuffmanCoder coder(input, output);
                	coder.startCompressing();
		}
		else if (action == DECOMPRESS) {
			HuffmanDecoder decoder(input, output);
            		decoder.startDecompressing();
		}

        	output.close();
		input.close();



	}
	catch (std::ios_base::failure e) {
		std::cerr << "Exception opening/reading/closing file" << std::endl;
	}


	unsigned int et = clock();
	unsigned int time = et - st;
	std :: cout << "time " << time << " ms" << std::endl;
	return 0;

}
