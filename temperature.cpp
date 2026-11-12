#include "temperature.h"

	Temperature::Temperature(double t, char s) : temper(t), scale(s) {}
	
	void Temperature::set(double t, char s)  { temper=t; scale=s; }
	 
	double Temperature::toC() { 
		
		if( scale == 'C' ) return temper ;
		else if ( scale == 'K' ) return temper - 273.15;
		return (temper - 32.0) / 1.8 ; //F
		}
	
       void Temperature::print()  {
        std::cout<<"("<<temper<<", "<<scale<<")";
    }
    
    double Temperature::gettemper() { 
		return temper; 
		}
		
    char Temperature::getscale() {
		 return scale; 
		 }
