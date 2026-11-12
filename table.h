#include "temperature.h"

	class Table {
		
		 int numstrok;
		 int numstolb;
		Temperature** temp;
		
		public:
		Table( int n = 0,  int k =0);
		Table(const Table& other);
       Table& operator=(const Table& other);
	bool sredn(int strok, double* result);
		bool min_in_strok( int strok, double* minimum);
  bool maxtable(double* maximum);
Table operator+(const Table& other);
		~Table();
		 bool readFromFile(const std::string& filename);
	  void print();
    
	};
