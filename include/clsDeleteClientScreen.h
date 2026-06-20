#pragma once
#include "clsBankClient.h"
#include <iostream>
#include "clsScreen.h"
class clsDeleteClientScreen : protected clsScreen
{
private:
    static void _Print(clsBankClient& client)
    {
        std::cout << "\nClient Card:";
        std::cout << "\n___________________";
        std::cout << "\nFirstName   : " << client.FirstName;
        std::cout << "\nLastName    : " << client.LastName;
        std::cout << "\nFull Name   : " << client.FullName();
        std::cout << "\nEmail       : " << client.Email;
        std::cout << "\nPhone       : " << client.Phone;
        std::cout << "\nAcc. Number : " << client.GetAccountNumber();
        std::cout << "\nPin Code    : " << client.GetPinCode();
        std::cout << "\nBalance     : " << client.GetAccountBalance();
        std::cout << "\n___________________\n";
    }

public:
    static void ShowDeleteClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\tDelete Screen");

            std::string AccountNumber;
            std::cout << "Please enter the AccountNumber?\n";
            AccountNumber = clsInputValidate::ReadString();

            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                std::cout << "The Client Is NOT Exist! Please try again?\n";
                AccountNumber = clsInputValidate::ReadString();
            }
            clsBankClient Client = clsBankClient::Find(AccountNumber);
            Client.Print();

            std::cout << "\nAre you sure you want to delete this account?  Y/N: ";
            char Sure = 'N';
            std::cin >> Sure;

            if (toupper(Sure) == 'Y')
            {
                if (Client.Delete())
                {
                    std::cout << "\nClient Deleted Successfully :)\n";
                    _Print(Client);
                }
                else
                {
                    std::cout << "\nError Client Was not Deleted\n";
                }

            }
    }
};

