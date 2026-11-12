#include <iostream>
#include <fstream>

class Temperature{
	
	double temper;
	char scale;
	
	public:
	
	Temperature(double t=0.0, char s='C');
	 void set(double t, char s);
	 
	double toC();
	
       void print();
    
    double gettemper();
		
    char getscale();
	
	};
