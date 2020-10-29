#include <iostream>
#include <fstream>
#include "../datastructures/stack/Stack.h"

#ifndef RPNCALC_H
#define RPNCALC_H

class RPNCalc
{
public:

	/* constructor */
	RPNCalc();

	/*destructor */
	~RPNCalc();

	/* run function 
	 * Launches a process  like dc’s command loop, reading in commands
     * from input. */
	void run(std::istream &in, std::ostream &out);

private:

	Stack<double> doubleStack;

	/* opens input file, reads contents as a commandline */
	void runOnFile(std::istream &in, std::ostream &out);

    /* Evaluate calculator input, write to outstream
    * return true if valid command/operator read */
	bool evalWrite(std::string arg, std::ostream &outfile);

	/* if string can be converted to double, converts string to double,
	 * returns true, and initializes passed variable with that double. */
	bool gotDouble(std::string arg, double *val);
    
    /* print top value */
    void print(std::ostream &outfile);

    /* Operators
     * Pop values, evaluate operation, push result */
	void add      (std::ostream &outfile);
	void subtract (std::ostream &outfile);
	void multiply (std::ostream &outfile);
	void divide   (std::ostream &outfile);    
    void exponent (std::ostream &outfile);
    void factorial(std::ostream &outfile);

    /* Iterative math functions */
    double exponentMathit  (double x, double n);
    double factorialMathit (double x);

    /* Recursive math functions */
    double exponentMathrec (double x, double n);   
    double factorialMathrec(double x);

};

#endif
