#pragma once

#include <iostream>
#include <vector>
#include <fstream>



struct 
stClientData
{
    std::string AccountNumber = "";
    std::string PINCode = "";
    std::string Name = "";
    std::string PhoneNumber = "";
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

enum enMenuOptions {
    QuickWithdraw       = 1,    NormalWithdraw  = 2,     Deposit    = 3,
    CheckBalance        = 4,    Logout          = 5,
};


std::vector<std::string> 
SplitString(std::string line, std::string delim = "#//#")
{
    std::vector<std::string>vRecords;
    size_t pos = 0;
    std::string record = "";
    while ((pos = line.find(delim)) != std::string::npos)
    {
        record = line.substr(0, pos);
        if (record != "")
        {
            vRecords.push_back(record);
        }

        line.erase(0, pos + delim.length());
    }

    if (line != "")
    {
        vRecords.push_back(line);
    }

    return vRecords;
}


stClientData 
ConvertLineToRecord(std::string line)
{
    std::vector<std::string> vRecords = SplitString(line);
    stClientData ClientData;

    ClientData.AccountNumber = vRecords[0];
    ClientData.PINCode = vRecords[1];
    ClientData.Name = vRecords[2];
    ClientData.PhoneNumber = vRecords[3];
    ClientData.AccountBalance = std::stod(vRecords[4]);

    return ClientData;
}


namespace Load {
    std::vector<stClientData> 
    ClientsDataFromFile(std::string filename)
    {
        std::vector<stClientData> vClientsData;
        std::fstream file;
        file.open(filename, std::ios::in);
        if (file.is_open())
        {
            stClientData ClientData;
            std::string line = "";
            while (std::getline(file, line))
            {
                ClientData = ConvertLineToRecord(line);
                vClientsData.push_back(ClientData);
            }

            file.close();
        }
        return vClientsData;
    }
}