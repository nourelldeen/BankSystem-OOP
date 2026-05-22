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
        cout << "\Pin Code     : " << client.GetPinCode();
        cout << "\nBalance     : " << client.GetAccountBalance();
        cout << "\n___________________\n";

    }
public:
    static void AddNewClient()
    {
        _DrawScreenHeader("\tAdd New Client");

        string AccountNumber;
        cout << "Please enter the AccountNumber?\n";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "The Client Is Exist! Please enter another PinCode?\n";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClient(AccountNumber);
        clsBankClient::GetInfoFromUser(NewClient);
        clsBankClient::AddNewClientToFill(NewClient);
                _Print(NewClient);    }
};

