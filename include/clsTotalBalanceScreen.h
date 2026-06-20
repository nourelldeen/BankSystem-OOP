#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"


class clsTotalBalanceScreen : public clsScreen
{

    static void _PrintBalanceInfoHeader(size_t ClientsNum)
    {
        std::cout << "\t\t\t\t\t\t Client List (" << ClientsNum << ") Client(s). \n\n";
        std::cout << "____________________________________________________________________________________________________________________\n\n";
        std::cout << std::setw(20) << std::left << "| Account Number";
        std::cout << std::setw(40) << std::left << "| Client Name";
        std::cout << std::setw(20) << std::left << "| Balance";
        std::cout << "\n____________________________________________________________________________________________________________________\n\n";
    }

    static void _PrintBalanceInfo(clsBankClient Client)
    {
        std::cout << "| " << std::setw(18) << Client.GetAccountNumber();
        std::cout << "| " << std::setw(38) << Client.FullName();
        std::cout << "| " << std::setw(18) << Client.GetAccountBalance();
    }

    static float _CalculateTotalBalance(std::vector<clsBankClient>& vClientInfo)
    {
        float TotalBalance = 0.0;
        for (clsBankClient& Client : vClientInfo)
            TotalBalance += Client.GetAccountBalance();
        return TotalBalance;
    }

public:
    static void PrintClientBalanceList()
    {
        _DrawScreenHeader("\t  Total Balance Screen");
        
        std::vector<clsBankClient> vFileData = clsBankClient::GetClientsList();

        _PrintBalanceInfoHeader(vFileData.size());

        for (clsBankClient& Client : vFileData)
        {
            _PrintBalanceInfo(Client);
            std::cout << std::endl;
        }
        float TotalBalances = _CalculateTotalBalance(vFileData);
        std::cout << "\n____________________________________________________________________________________________________________________\n\n\n";
        std::cout << "\t\t\t\t Total Balance = " << TotalBalances << "\n\n";
        std::cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";

    }

};

