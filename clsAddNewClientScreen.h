#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
class clsAddNewClientScreen : protected clsScreen
{
private:
    static void _Print(clsBankClient& client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.FirstName;
        cout << "\nLastName    : " << client.LastName;
        cout << "\nFull Name   : " << client.FullName();
        cout << "\nEmail       : " << client.Email;
        cout << "\nPhone       : " << client.Phone;
        cout << "\nAcc. Number : " << client.GetAccountNumber();
        cout << "\nPin Code    : " << client.GetPinCode();
        cout << "\nBalance     : " << client.GetAccountBalance();
        cout << "\n___________________\n";

    }
public:
    static void AddNewClient()
    {
        _DrawScreenHeader("\tAdd New Client");

        clsBankClient::AddNewClient();

    }
};

