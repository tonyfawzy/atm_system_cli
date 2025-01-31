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
}