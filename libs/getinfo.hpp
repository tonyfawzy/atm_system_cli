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
    
}