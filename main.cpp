#include "table.h"
#include <iostream>

int main ()
{ 

int com=-1;
Table<Temperature> t1,t2,t3;
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
		 Table<Temperature> summa(t3);
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
