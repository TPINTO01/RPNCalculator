CXX      = clang++
CXXFLAGS = -std=c++11 -g3 -Wall -Wextra
LDFLAGS  = -g3
 
#
RPNCalc: main.o RPNCalc.o 
	${CXX} ${LDFLAGS} -o RPNCalc main.o RPNCalc.o 

#
#testRPNCalc: testRPNCalc.cpp RPNCalc.o
RPNCalc.o:     RPNCalc.cpp  

#
clean:
	rm RPNCalc *.o 

