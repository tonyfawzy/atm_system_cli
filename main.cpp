#include <iostream>
#include <string>
#include <vector>

#include "libs/drw.hpp"
#include "libs/getinfo.hpp"
#include "libs/handleDB.hpp"


stClientData CurrentClient;

const std::string ClientsFilename = "../simplebank/ClientsData.txt";

/* funcation declarations */
void login();
void ShowMainMenuOptions();


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
GoBackToMainMenuOptions()
{
    #ifdef _WIN32
        std::cout << "\n\nPress any key to go back to main menu...";
        system("pause>0");
        ShowMainMenuOptions();
    #else
        system("read -p \"\n\nPress any key to go back to main menu...\"");
        ShowMainMenuOptions();
    #endif

}

void
ShowClientBalance()
{
    std::string title = "Check Balance Screen";
    clearScreen();
    drw::header(title);

    std::cout << "Your Balance is: " << std::to_string(CurrentClient.AccountBalance) << std::endl;
}

void
PerfromMainMenuOption(enMenuOptions MenuOption)
{
    switch (MenuOption)
    {
    case enMenuOptions::QuickWithdraw:
        clearScreen();
        GoBackToMainMenuOptions();
        break;
    
    case enMenuOptions::NormalWithdraw:
        clearScreen();
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::Deposit:
        clearScreen();
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::CheckBalance:
        clearScreen();
        ShowClientBalance();
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::Logout:
        clearScreen();
        login();
        break;
 
    }
}

void
ShowMainMenuOptions()
{
    std::string title = "ATM Main Menu Screen";
    clearScreen();
    drw::header(title);

    std::cout << "\t[1] Quick withdraw.\n";
    std::cout << "\t[2] Normal withdraw.\n";
    std::cout << "\t[3] Deposit.\n";
    std::cout << "\t[4] Check Balance.\n";
    std::cout << "\t[5] Logout.\n";

    for (short i = 1; i <= title.length()*3; ++i) { std::cout << drw::divder; }
    std::cout << std::endl;
    PerfromMainMenuOption((enMenuOptions)getInfo::short_num("Choose what do you want to do? [1 to 5]"));
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
    
    ShowMainMenuOptions();
}

int main()
{
    login();

    return 0;
}