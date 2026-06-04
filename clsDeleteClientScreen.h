#pragma once
#include "clsBankClient.h"
#include <iostream>
#include "clsScreen.h"
class clsDeleteClientScreen : protected clsScreen
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
    static void ShowDeleteClientScreen()
    {
        _DrawScreenHeader("\tDelete Screen");

            string AccountNumber;
            cout << "Please enter the AccountNumber?\n";
            AccountNumber = clsInputValidate::ReadString();

            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "The Client Is NOT Exist! Please try again?\n";
                AccountNumber = clsInputValidate::ReadString();
            }
            clsBankClient Client = clsBankClient::Find(AccountNumber);
            Client.Print();

            cout << "\nAre you sure you want to delete this account?  Y/N: ";
            char Sure = 'N';
            cin >> Sure;

            if (toupper(Sure) == 'Y')
            {
                if (Client.Delete())
                {
                    cout << "\nClient Deleted Successfully :)\n";
                    _Print(Client);
                }
                else
                {
                    cout << "\nError Client Was not Deleted\n";
                }

            }
    }
};

