#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "../datastructures/stack/Stack.h"
#include "RPNCalc.h"

/* constructor */
RPNCalc::RPNCalc()
{}

/*destructor */
RPNCalc::~RPNCalc()
{}

/* Read in and evaluate RPNCalc arguments */
void RPNCalc::run(std::istream &in, std::ostream &out)
{
    std::string s;
    for (in >> s; not in.eof(); in >> s) {
    	double value;
        if (! evalWrite(s, out)) {
       	    if (s == "f" || s == "F") 
       		    runOnFile(in, out);
       	    else if (gotDouble(s, &value))
       		    doubleStack.push(value);
       	    else
                std::cerr << s << ": unimplemented" << std::endl;      		
        }
	}
}


/**************************************************************************
 *                                                                        *
 *                           PRIVATE MEMBERS                              *
 *                                                                        *
 **************************************************************************/

/* runOnFile */
void RPNCalc::runOnFile(std::istream &in, std::ostream &out)
{
	std::string   fileName;
    std::ifstream inFile;

	in >> fileName;	
	inFile.open(fileName.c_str());

	if (inFile.is_open()) {
        run(inFile, out);
		inFile.close();
	} else 
    	std::cerr << "Unable to open " << fileName << std::endl;
}

/* Evaluate calculator input, write to outstream
 * return true if valid command/operator read */
bool RPNCalc::evalWrite(std::string inputString, std::ostream &out)
{
    if (inputString == "q" || inputString == "Q") 
		exit(0);
	else if (inputString == "p" || inputString == "P") 
        print(out);
	else if (inputString == "c" || inputString == "C")
		doubleStack.clear();
    else if (inputString == "+") 
	    add(out);	
    else if (inputString == "-") 
		subtract(out);
    else if (inputString == "*")
        multiply(out);
    else if (inputString == "/")	
	    divide(out);
    else if (inputString == "^")	
	    exponent(out);
    else if (inputString == "!")	
	    factorial(out);
    else
        return false;

	return true;
}

/* Returns true if string s can be represented as double, assigns value to resultp */
bool RPNCalc::gotDouble(std::string s, double *resultp)
{
        return sscanf(s.c_str(), "%lf", resultp) == 1;
}

void RPNCalc::print(std::ostream &out)
{
    if (doubleStack.isEmpty()) 
        out.write("Empty", 6);
    else {
        std::string top = std::to_string(doubleStack.top());
		out.write(top.c_str(), top.size());
    }
    out.put('\n');
}

void RPNCalc::add(std::ostream &out)
{
    if (doubleStack.size() < 2)
        out.write("Too few operands \n", 19);
    else {        
	    double n1 = doubleStack.pop();
	    double n2 = doubleStack.pop();	
	    doubleStack.push(n2 + n1);
    }
}

void RPNCalc::subtract(std::ostream &out)
{
    if (doubleStack.size() < 2)
        out.write("Too few operands \n", 19);
    else {
	    double n1 = doubleStack.pop();
	    double n2 = doubleStack.pop();
	    doubleStack.push(n2 - n1);
    }
}

void RPNCalc::multiply(std::ostream &out)
{
    if (doubleStack.size() < 2)
        out.write("Too few operands \n", 19);
    else {
	    double n1 = doubleStack.pop();
	    double n2 = doubleStack.pop();
	    doubleStack.push(n2 * n1);
    }
}

void RPNCalc::divide(std::ostream &out)
{
    if (doubleStack.size() < 2)
        out.write("Too few operands\n", 19);
    else {
	    double n1 = doubleStack.pop();
	    double n2 = doubleStack.pop();
	    doubleStack.push(n2 / n1);
    }
}

void RPNCalc::exponent(std::ostream &out)
{
    if (doubleStack.size() < 2)
        out.write("Too few operands \n", 19);
    else {
	    double e = doubleStack.pop();
	    double b = doubleStack.pop();
	    doubleStack.push(exponentMathit(b, e)); // b^eS
    }
}

void RPNCalc::factorial(std::ostream &out)
{
    if (doubleStack.size() < 1)
        out.write("Too few operands \n", 19);
    else {
	    double n = doubleStack.pop();
	    doubleStack.push(factorialMathit(n)); // n!
    }
}

double RPNCalc::exponentMathit(double b, double e)
{
    double accum = b;
    if (!e) return 1;

    for (; e > 1; --e) 
        accum = accum * b;

    return accum;
}

double RPNCalc::factorialMathit(double x)
{
    double accum = 1;
    
    for (int i = x; i > 0; --i) 
        accum = accum * i;

    return accum;
}

double RPNCalc::exponentMathrec(double b, double e)
{
    if (e) return b * exponentMathrec(b, e - 1); else return 1;
}

double RPNCalc::factorialMathrec(double x)
{
    if (x) return x * factorialMathrec(x - 1); else return 1;
}
