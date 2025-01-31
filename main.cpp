#include <iostream>
#include <string>
#include <vector>

#include "libs/drw.hpp"
#include "libs/getinfo.hpp"
#include "libs/handleDB.hpp"


stClientData CurrentClient;

const std::string ClientsFilename = "../simplebank/ClientsData.txt";

void 
clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


bool
FindAccountByAccountNumberAndPIN (std::string AccountNumber, std::string PIN, stClientData& ClientData)
{
    std::vector<stClientData> vClientsData = Load::ClientsDataFromFile(ClientsFilename);

    for (stClientData& C : vClientsData) {
        if (C.AccountNumber == AccountNumber && C.PINCode == PIN) {
            ClientData = C;
            return true;
        }
    }
    return false;

}

bool
LoadAccountInfo (std::string AccountNumber, std::string PIN)
{
    return FindAccountByAccountNumberAndPIN(AccountNumber, PIN, CurrentClient);
}

void
login()
{
    std::string title = "Login Screen";
    clearScreen();
    drw::header(title);

    std::string AccountNumber = getInfo::string("Enter Account Number");
    std::string PINCode = getInfo::string("Enter PIN Code");

    while (!LoadAccountInfo(AccountNumber, PINCode))
    {
        clearScreen();
        drw::header(title);
        std::cout << "Invalid Account Number/PINCode!\n";
        AccountNumber = getInfo::string("Enter Account Number");
        PINCode = getInfo::string("Enter PIN Code");
    }
    

}

int main()
{
    login();

    return 0;
}