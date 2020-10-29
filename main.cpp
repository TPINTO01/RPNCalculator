#include <iostream>
#include <fstream>
#include "RPNCalc.h"

void usage(char *progName);

int main(int argc, char *argv[])
{
	RPNCalc calculator;

    if (argc == 1)
	    calculator.run(std::cin, std::cout);

    else if (argc == 2 || argc == 3) {
        char *inFileName = argv[1];
        std::ifstream inFile;	    
	    inFile.open(inFileName);
	    if (inFile.is_open()) {
            if (argc == 3) {
                char *outFileName = argv[2];
                std::ofstream outFile;	    
	            outFile.open(outFileName);
	            if (outFile.is_open()) {
                    calculator.run(inFile, outFile); 
                    outFile.close();
                } else 
        	        std::cerr << "Unable to open " << outFileName << std::endl;
            } else 
                calculator.run(inFile, std::cout);
		    inFile.close();
	    } else 
    	    std::cerr << "Unable to open " << inFileName << std::endl;    
    } else
        usage(argv[0]);

	return 0;
}

void usage(char *progName)
{
    std::cerr << "usage: " << progName <<  std::endl 
              << "       " << progName << " input_file " << std::endl
              << "       " << progName << " input_file output_file " <<std::endl;
}
