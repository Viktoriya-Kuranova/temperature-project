#include "temperature.h"
#include <vector>

	template <typename T>
	class Table {
		
		 int numstrok;
		 int numstolb;
		std::vector<std::vector<T>> temp;
		
		public:
		Table( int n = 0,  int k =0);
		Table(const Table<T>& other);
       Table<T>& operator=(const Table<T>& other);
	bool sredn(int strok, double* result);
		bool min_in_strok( int strok, double* minimum);
  bool maxtable(double* maximum);
Table<T> operator+(const Table<T>& other);
		~Table()= default;
		 bool readFromFile(const std::string& filename);
	  void print();
    
	};

extern template class Table<Temperature>;
