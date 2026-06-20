#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"


class clsTotalBalanceScreen : public clsScreen
{

    static void _PrintBalanceInfoHeader(size_t ClientsNum)
    {
        cout << "\t\t\t\t\t\t Client List (" << ClientsNum << ") Client(s). \n\n";
        cout << "____________________________________________________________________________________________________________________\n\n";
        cout << setw(20) << left << "| Account Number";
        cout << setw(40) << left << "| Client Name";
        cout << setw(20) << left << "| Balance";
        cout << "\n____________________________________________________________________________________________________________________\n\n";
    }

    static void _PrintBalanceInfo(clsBankClient Client)
    {
        cout << "| " << setw(18) << Client.GetAccountNumber();
        cout << "| " << setw(38) << Client.FullName();
        cout << "| " << setw(18) << Client.GetAccountBalance();
    }

    static float _CalculateTotalBalance(vector<clsBankClient>& vClientInfo)
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
        
        vector<clsBankClient> vFileData = clsBankClient::GetClientsList();

        _PrintBalanceInfoHeader(vFileData.size());

        for (clsBankClient& Client : vFileData)
        {
            _PrintBalanceInfo(Client);
            cout << endl;
        }
        float TotalBalances = _CalculateTotalBalance(vFileData);
        cout << "\n____________________________________________________________________________________________________________________\n\n\n";
        cout << "\t\t\t\t Total Balance = " << TotalBalances << "\n\n";
        cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";

    }

};

