#include "table.h"
#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

namespace opt = boost::program_options;

int main(int argc, char** argv)
{
    opt::options_description desc("Опции программы");
    desc.add_options()
        ("help,h", "показать помощь")
        ("input1", opt::value<std::string>()->default_value("input1.txt"),
                   "файл с первой таблицей")
        ("input2", opt::value<std::string>()->default_value("input2.txt"),
                   "файл со второй таблицей")
        ("config,c", opt::value<std::string>(),
                     "конфиг-файл с параметрами");

    opt::variables_map vm;

    try {
        opt::store(opt::parse_command_line(argc, argv, desc), vm);

        if (vm.count("config")) {
            std::ifstream cfg(vm["config"].as<std::string>());
            if (!cfg.is_open()) {
                std::cout << "Ошибка: не удалось открыть конфиг-файл "
                          << vm["config"].as<std::string>() << std::endl;
                return 1;
            }
            opt::store(opt::parse_config_file(cfg, desc), vm);
        }

        opt::notify(vm);
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка разбора параметров: " << e.what() << std::endl;
        std::cout << desc << std::endl;
        return 1;
    }

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    std::string file1 = vm["input1"].as<std::string>();
    std::string file2 = vm["input2"].as<std::string>();

    Table t1, t2, t3;
    if (!t1.readFromFile(file1) || !t2.readFromFile(file2)) {
        return 1;
    }

    int com = -1;
    int strok;
    while (com != 0) {
        std::cout << "1 - Прочитать и вывести" << std::endl
                  << "2 - Средняя температура по строке" << std::endl
                  << "3 - Минимальная температура по строке" << std::endl
                  << "4 - Сумма двух таблиц" << std::endl
                  << "5 - Максимальная температура для таблицы" << std::endl
                  << "0 -  Выход из программы" << std::endl;
        std::cin >> com;
        switch (com) {
        case 1:
            if (!t1.readFromFile(file1) || !t2.readFromFile(file2)) {
                return 1;
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

        case 4: {
            t3 = t1 + t2;
            Table summa(t3);
            std::cout << "Результат суммы двух таблиц : " << std::endl;
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
            return 0;
        default:
            std::cout << "Такой команды нет в списке" << std::endl;
        }
    }
    return 0;
}
