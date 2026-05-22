#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

class clsClientListScreen :protected clsScreen
{


    static void _PrintClientListHeader()
    {
        cout << "____________________________________________________________________________________________________________________\n\n";
        cout << setw(20) << left << "| Account Number";
        cout << setw(20) << left << "| Pin Code";
        cout << setw(40) << left << "| Client Name";
        cout << setw(20) << left << "| Phone";
        cout << setw(20) << left << "| Balance";
        cout << "\n____________________________________________________________________________________________________________________\n\n";
    }

    static void _PrintListInfo(clsBankClient Client)
    {
        cout << "| " << setw(18) << Client.GetAccountNumber();
        cout << "| " << setw(18) << Client.GetPinCode();
        cout << "| " << setw(38) << Client.FullName();
        cout << "| " << setw(18) << Client.GetPhone();
        cout << "| " << setw(18) << Client.GetAccountBalance();
    }

public:
    static void ShowClientList()
    {
        vector <clsBankClient> vClients = clsBankClient::GetDataFromFileToVector();

        string Title = "\t  Client List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        system("cls");

        _DrawScreenHeader(Title, SubTitle);
        _PrintClientListHeader();
        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

        for (clsBankClient& Client : vClients)
        {
            _PrintListInfo(Client);
        }
        cout << "\n____________________________________________________________________________________________________________________\n\n\n";

    }

};

