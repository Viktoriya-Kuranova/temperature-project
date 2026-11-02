#include <iostream>
#include <fstream>

class Temperature{
	
	double temper;
	char scale;
	
	public:
	
	Temperature(double t=0.0, char s='C') : temper(t), scale(s) {}
	 void set(double t, char s)  { temper=t; scale=s; }
	 
	double toC() { 
		
		if( scale == 'C' ) return temper ;
		else if ( scale == 'K' ) return temper - 273.15;
		return (temper - 32.0) / 1.8 ; //F
		}
	
       void print()  {
        std::cout<<"("<<temper<<", "<<scale<<")";
    }
    
    double gettemper() { 
		return temper; 
		}
		
    char getscale() {
		 return scale; 
		 }
	
	};
	
	class Table {
		
		 int numstrok;
		 int numstolb;
		Temperature** temp;
		
		public:
		Table( int n = 0,  int k =0) : numstrok(n), numstolb(k), temp(nullptr)
		{ 
			if(n > 0 && k > 0) {
			
				temp= new  Temperature*[n];
				if(!temp)
				{
					std::cout<<"Ошибка выделения памяти"<<std::endl;
					return;
					}
				for(int i=0; i<n; i++)
			{
			  temp[i] = new  Temperature[k];
				  if (!temp[i]) {
                std::cout << "Ошибка выделение памяти"<< std::endl;
                for ( int j = 0; j < i; j++) {
                   delete[] temp[j];
				     }
				       delete[] temp;
                   temp = nullptr;
                     numstolb=0;
                     numstrok=0;
                     return; 
				}
				
			   } 
			} 
		}
		
		Table(const Table& other) ///konst kop
		{ 
    numstrok = other.numstrok;
    numstolb = other.numstolb;

    if (numstrok > 0 && numstolb > 0) {
        temp = new Temperature*[numstrok];
        if(!temp){
			std::cout << "Ошибка выделение памяти"<< std::endl;
			}
        for ( int i = 0; i < numstrok; i++) {
            temp[i] = new Temperature[numstolb];
            if(!temp[i]){
				std::cout << "Ошибка выделение памяти"<< std::endl;
				}
            for ( int j = 0; j < numstolb; j++) {
                temp[i][j] = other.temp[i][j]; 
            }
        }
    } else {
        temp = nullptr;
            }
       }
       
       Table& operator=(const Table& other) {
    if (this == &other) return *this;

    if (temp) {
        for (int i = 0; i < numstrok; i++) delete[] temp[i];
        delete[] temp;
    }

    numstrok = other.numstrok;
    numstolb = other.numstolb;

    if (numstrok && numstolb) {
        temp = new Temperature*[numstrok];
        if(!temp){
			std::cout<<"Ошибка выделения памяти"<<std::endl;
			}
        for ( int i = 0; i < numstrok; i++) {
            temp[i] = new Temperature[numstolb];
            if(!temp[i]){
				std::cout<<"Ошибка выделения памяти"<<std::endl;
				}
            for (int j = 0; j < numstolb; j++)
                temp[i][j] = other.temp[i][j];
        }
    } else {
        temp = nullptr;
    }
    return *this;
}

	bool sredn(int strok, double* result) {
    
    if (strok >= numstrok || strok<0) {
        std::cout << "Ошибка такой строки нет!"<< std::endl;
        return false;
    }

    double sum = 0;
    for (int i = 0; i < numstolb; i++)
        sum += temp[strok][i].toC();

    *result = sum / numstolb;  
    return true;              
}

		
		bool min_in_strok( int strok, double* minimum) { 
    if (!minimum) return false;
    
    if (strok >= numstrok || strok<0) {
        std::cout << "Ошибка неверный номер строки" << std::endl;
        return false;
    }
    double tmin= temp[strok][0].toC();
    for (int i = 1; i < numstolb; i++) {
        double val = temp[strok][i].toC();
        if (val < tmin) tmin = val;
    }
    *minimum = tmin;
    return true;
}
  
  bool maxtable(double* maximum) {  
    if (!maximum) return false;
    double max = temp[0][0].toC();
    for ( int i = 0; i < numstrok; i++) {
        for ( int j = 0; j < numstolb; j++) {
            double val = temp[i][j].toC();
            if (val > max) max = val;
        }
    }
    *maximum = max;
    return true;
}
Table operator+(const Table& other) { ///peregruzka
    if (numstrok != other.numstrok || numstolb != other.numstolb) {
        std::cout << "Ошибка таблицы разных размеров сложение невозможно!" << std::endl;
        return Table(); 
    }

    Table result(numstrok, numstolb);

    for ( int i = 0; i < numstrok; i++) {
        for ( int j = 0; j < numstolb; j++) {
    
            double valt1 = temp[i][j].gettemper();
            char   sct1 = temp[i][j].getscale();
            double valt2 = other.temp[i][j].gettemper();
            char   sct2 = other.temp[i][j].getscale();

            double valt2sct1;
            if (sct1 == sct2) {
                valt2sct1 = valt2; 
            } else {
                double valt2C = (sct2=='C') ? valt2 : (sct2=='K') ? (valt2 - 273.15)  : (valt2 - 32.0) / 1.8; 
              
                valt2sct1 = (sct1=='C') ? valt2C  : (sct1=='K') ? (valt2C + 273.15)  : (valt2C * 1.8 + 32.0);  
            }

            double sum = valt1 + valt2sct1;           
            result.temp[i][j].set(sum, sct1);       
        }
    }
    return result;
}
  
		~Table() {
			
			if(temp)
			{
				for( int i = 0;i<numstrok;i++)
				delete[] temp[i];
				delete[] temp;
				}
			}
		 bool readFromFile(const std::string& filename) {
        std::ifstream fin(filename);
        if (!fin.is_open()) {
            std::cout << "Ошибка при открытии файла "  << std::endl;
            return false;
        }
        int tnumstrok,tnumstolb;
        if (!(fin >> tnumstrok >> tnumstolb)) {
        std::cout << "Ошибка не удалось прочитать размеры таблицы"<<std::endl;
        return false;
    }
        
        if (tnumstrok <= 0 || tnumstolb <= 0) {
        std::cout << "Ошибка неверные размеры таблицы" << std::endl;
        return false;
    }
    if (temp) {
    for ( int i = 0; i < numstrok; i++)
        delete[] temp[i];
    delete[] temp;
    temp = nullptr;
}

       numstrok = tnumstrok;
       numstolb = tnumstolb;
        temp = new Temperature*[numstrok];
          if (!temp) {
        std::cout << "Ошибка выделения памяти" << std::endl;
        return false;
    }
        for ( int i = 0; i < numstrok; i++){
            temp[i] = new Temperature[numstolb];
         if (!temp[i]) {
           std::cout << "Ошибка выделения памяти " << std::endl;
            temp = nullptr;
            numstolb=0;
            numstrok=0;
        return false;
    
    }
   } 
    for (int i = 0; i < numstrok; i++) {
        for (int j = 0; j < numstolb; j++) {
            double val;
            char sc;

            if (!(fin >> val >> sc)) {
                if (fin.eof()) {
                    std::cout << "Ошибка в файле меньше данных чем указано размерами таблицы!" << std::endl;
                } else {
                    std::cout << "Ошибка неверный формат данных в ячейке" << std::endl;
                }
                return false;
            }
            if (sc != 'C' && sc != 'K' && sc != 'F') {
                std::cout << "Ошибка неизвестная шкала " << std::endl;
                return false;
            }

            if (sc == 'K' && val <= 0) {
                std::cout << "Ошибка температура не имеет физического смысла" << std::endl;
                return false;
            }
            if (sc == 'C' && val <=-273.15) {
          std::cout << "Ошибка температура не имеет физического смысла"<<std::endl;
    return false;
}
       if (sc == 'F' && val <= -459.67) {
    std::cout << "Ошибка температура не имеет физического смысла"<<std::endl;
    return false;
                   }
            temp[i][j].set(val, sc);
        }
    }
      double dopval;
       char   dopsc;
        if (fin >> dopval >> dopsc) {
    std::cout << "Ошибка в файле больше данных чем указано размерами таблицы!" << std::endl;
    return false;
}
        
        fin.close();
        return true;
       } 
  
	  
	 
	  void print()  {
        for ( int i = 0; i < numstrok; i++) {
            for ( int j = 0; j < numstolb; j++) {
                temp[i][j].print();
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }
    
	};
	

int main ()
{ 

int com=-1;
Table t1,t2,t3;
 if (!t1.readFromFile("input1.txt") || !t2.readFromFile("input2.txt")) {
        exit(1);
    }
 int strok;
while(com!=0)
{ std::cout << "1 - Прочитать и вывести"<<std::endl
	   << "2 - Средняя температура по строке"<<std::endl
	   <<"3 - Минимальная температура по строке"<<std::endl
	   <<"4 - Сумма двух таблиц"<<std::endl
	   <<"5 - Максимальная температура для таблицы"<<std::endl
	   <<"0 -  Выход из программы"<<std::endl;
	   std::cin>>com;
	switch(com)
	{
		case 1:
		   if (!t1.readFromFile("input1.txt") || !t2.readFromFile("input2.txt")) {
                  exit(1);
               }
                    std::cout << "\nТаблица 1:\n";
                    t1.print();
                    std::cout << "\nТаблица 2:\n";
                    t2.print();
		 break;
		 
		 case 2: {
	 std::cout << "Введите номер строки: ";
    std::cin >> strok;

    double sr; 
    if (t1.sredn(strok - 1, &sr)) {
        std::cout << "Средняя температура: " << sr << " C" << std::endl;
    }
    break;
}  
		 
		 case 3: {
    std::cout << "Введите номер строки" << std::endl;
    std::cin >> strok;
    double minimum;
    if (t1.min_in_strok(strok - 1, &minimum)) {
        std::cout << "Минимальная температура в " << strok
             << " строке в Цельсиях : " << minimum << std::endl;
    }
    break;
}
		 
	 
		 case 4:{
		 t3=t1+t2;
		 Table summa(t3);
		 std::cout<<"Результат суммы двух таблиц : "<<std::endl;
		 t3.print();
		 break;
}
       case 5: {
    double maximum;
    if (t1.maxtable(&maximum)) {
        std::cout << "Максимальная температура в таблице в Цельсиях  : " << maximum << std::endl;
    }
    break;
}	 
		 case 0:
		 exit(0);
		default:
		 std::cout << "Такой команды нет в списке"<<std::endl;
		 
		}
		
	}

return 0;
}

