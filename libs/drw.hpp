#include <iostream>


namespace drw {

    const char divder = '-';

    void
    header(std::string title, char divider_char = divder)
    {
        
        for (short i = 1; i <= title.length()*3; ++i) { std::cout << divider_char; }

        std::cout << std::endl;

        for (short i = 1; i <= title.length(); ++i) { std::cout << " "; }

        std::cout << title << std::endl;

        for (short i = 1; i <= title.length()*3; ++i) { std::cout << divider_char; }

        std::cout << std::endl;
    }

}