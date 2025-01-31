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
void ShowQuickWithdrawOptions();

enum
enQuickWithdraw {
    twenty          = 1,    fifty           = 2,    hundred     = 3,
    two_hundred     = 4,    four_hundred    = 5,    six_hundred = 6,
    eight_hundred   = 7,    thousand        = 8,    eExit       = 9,
};

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
    std::vector<stClientData> vClientsData = LoadData::ClientsDataFromFile(ClientsFilename);

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
GoBackToQuickWithdrawOptions()
{
    #ifdef _WIN32
        std::cout << "\n\nPress any key to go back to quick withdraw menu...";
        system("pause>0");
        ShowQuickWithdrawOptions();
    #else
        system("read -p \"\n\nPress any key to go back to quick withdraw menu...\"");
        ShowQuickWithdrawOptions();
    #endif

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
ClientBalance()
{
    std::cout << "Your Balance is: " << CurrentClient.AccountBalance << std::endl;
}

void
ShowClientBalance()
{
    clearScreen();
    drw::header("Check Balance Screen");

    ClientBalance();
}


bool
PerformDepositByAccountNumber(std::string AccountNumber, double amount, std::vector<stClientData>& vClientsData)
{

    char confirm = getInfo::character("Are you sure you want perform this transaction? y/n");

    if (tolower(confirm) == 'y')
    {
        for (stClientData& C : vClientsData)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += amount;
                SaveData::ClientsDataToFile(vClientsData, ClientsFilename);
                CurrentClient.AccountBalance = C.AccountBalance;
                std::cout << "Done successfully. New balance is: " << C.AccountBalance << std::endl;
                break;
            }
        }
        return true;
    }
    else {
        return false;
    }
}


void
PerformQuickWithdraw(double amount)
{
    if (amount > CurrentClient.AccountBalance)
    {
        std::cout << "\nThe amount exceeds your balance, make another choice." << std::endl;
        GoBackToQuickWithdrawOptions();
        
    }

    std::vector<stClientData> vClientsData = LoadData::ClientsDataFromFile(ClientsFilename);

    PerformDepositByAccountNumber(CurrentClient.AccountNumber, amount*-1, vClientsData);
}




void
PerfromQuickWithdrawOption (enQuickWithdraw QuickWithdraw)
{
    switch (QuickWithdraw)
    {
    case enQuickWithdraw::twenty:
        PerformQuickWithdraw(20);
        GoBackToQuickWithdrawOptions();
        break;
    case enQuickWithdraw::fifty:
        PerformQuickWithdraw(50);
        GoBackToQuickWithdrawOptions();
        break;
    case enQuickWithdraw::hundred:
        PerformQuickWithdraw(100);
        GoBackToQuickWithdrawOptions();
        break;
    case enQuickWithdraw::two_hundred:
        PerformQuickWithdraw(200);
        GoBackToQuickWithdrawOptions();
        break;
    case enQuickWithdraw::four_hundred:
        PerformQuickWithdraw(400);
        GoBackToQuickWithdrawOptions();
        break;
    case enQuickWithdraw::six_hundred:
        PerformQuickWithdraw(600);
        GoBackToQuickWithdrawOptions();
        break;
    case enQuickWithdraw::eight_hundred:
        PerformQuickWithdraw(800);
        GoBackToQuickWithdrawOptions();
        break;
    case enQuickWithdraw::thousand:
        PerformQuickWithdraw(1000);
        GoBackToQuickWithdrawOptions();
        break;
    case enQuickWithdraw::eExit:
        clearScreen();
        ShowMainMenuOptions();
        break;
    }
}

void
ShowQuickWithdrawOptions()
{
    std::string title = "Quick Withdraw Screen";
    clearScreen();
    drw::header(title);

    std::cout << "\t[1] 20\t";
    std::cout << "\t[2] 50\n";
    std::cout << "\t[3] 100\t";
    std::cout << "\t[4] 200\n";
    std::cout << "\t[5] 400\t";
    std::cout << "\t[6] 600\n";
    std::cout << "\t[7] 800\t";
    std::cout << "\t[8] 1000\n";
    std::cout << "\t[9] Exit\n";

    drw::divider(title);
    ClientBalance();
    PerfromQuickWithdrawOption((enQuickWithdraw)getInfo::short_num("Choose what to withdraw from [1] to [8]"));
}


void
PerformDeposit()
{
    drw::header("Deposit Screen");

    double amount = getInfo::double_num("Enter a positive deposit amount");

    while (amount < 0)
    {
        amount = getInfo::double_num("Enter a positive deposit amount");
    }

    std::vector<stClientData> vClientsData = LoadData::ClientsDataFromFile(ClientsFilename);

    PerformDepositByAccountNumber(CurrentClient.AccountNumber, amount, vClientsData);
}

void
PerformNormalWithdraw()
{
    drw::header("Normal Withdraw Screen");
    
    double amount = getInfo::double_num("Enter an amount multiple of 5's");
    while ((int)amount % 5 != 0)
    {
        amount = getInfo::double_num("Enter an amount multiple of 5's");
    }

    std::vector<stClientData> vClientsData = LoadData::ClientsDataFromFile(ClientsFilename);
    PerformDepositByAccountNumber(CurrentClient.AccountNumber, amount*-1, vClientsData);
}

void
PerfromMainMenuOption(enMenuOptions MenuOption)
{
    switch (MenuOption)
    {
    case enMenuOptions::QuickWithdraw:
        clearScreen();
        ShowQuickWithdrawOptions();
        GoBackToMainMenuOptions();
        break;
    
    case enMenuOptions::NormalWithdraw:
        clearScreen();
        PerformNormalWithdraw();
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::Deposit:
        clearScreen();
        PerformDeposit();
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

    drw::divider(title);
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