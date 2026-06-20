#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
class clsUpdateClientScreen : public clsScreen
{
private :
    
    static void ReadClientInfo(clsBankClient& Client)
    {
        std::cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        std::cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        std::cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        std::cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        std::cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        std::cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

public:

    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\tUpdate Client Screen");

        std::string AccountNumber = "";

        std::cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            std::cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        Client.Print();

        std::cout << "\nAre you sure you want to update this client y/n? ";

        char Answer = 'n';
        std::cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            std::cout << "\n\nUpdate Client Info:";
            std::cout << "\n____________________\n";


            ReadClientInfo(Client);

            clsBankClient::enSaveResults SaveResult;

            SaveResult = Client.Save();

            switch (SaveResult)
            {
            case  clsBankClient::enSaveResults::svSucceeded:
            {
                std::cout << "\nAccount Updated Successfully :-)\n";

                Client.Print();
                break;
            }
            case clsBankClient::enSaveResults::svFaildEmptyObject:
            {
                std::cout << "\nError account was not saved because it's Empty";
                break;

            }

            }

        }

    }
};
