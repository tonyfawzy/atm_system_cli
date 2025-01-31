#include <string>
#include <iostream>


namespace getInfo {

    std::string
    string(std::string message)
    {
        std::string txt = "";
        std::cout << message + "? "; std::getline(std::cin >> std::ws, txt);
        return txt;
    }

    short 
    short_num(std::string message)
    {
        short s_num = 0;
        std::cout << message + "? "; std::cin >> s_num; return s_num;
    }

    /*
    double 
    double_num(std::string message)
    {
        short d_num = 0;
        std::cout << message + "? "; std::cin >> d_num; return d_num;
    }
     */

    double 
    double_num(std::string message)
    {
        short d_num = 0;

        std::cout << message + "? ";
        while (true)
        {
            if (std::cin >> d_num)
            {
                return d_num;
            } else {
                std::cout << "[ERROR]: Please try again! " << message + "? ";
                std::cin.clear();
                while (std::cin.get() != '\n');
            }
        }
    }


    char 
    character(std::string message)
    {
        char _character = ' ';
        std::cout << message + "? "; std::cin >> _character; return _character;
    }
}