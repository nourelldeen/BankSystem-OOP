#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
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

    static void _PrintClient(clsBankClient Client)
    {
        std::cout << "\nClient Card:";
        std::cout << "\n___________________";
        std::cout << "\nFirstName   : " << Client.FirstName;
        std::cout << "\nLastName    : " << Client.LastName;
        std::cout << "\nFull Name   : " << Client.FullName();
        std::cout << "\nEmail       : " << Client.Email;
        std::cout << "\nPhone       : " << Client.Phone;
        std::cout << "\nAcc. Number : " << Client.GetAccountNumber();
        std::cout << "\nPassword    : " << Client.PinCode;
        std::cout << "\nBalance     : " << Client.AccountBalance;
        std::cout << "\n___________________\n";

    }

public:

    static void ShowAddNewClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;// this will exit the function and it will not continue
        }


        _DrawScreenHeader("\t  Add New Client Screen");

        std::string AccountNumber = "";

        std::cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            std::cout << "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);


        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case  clsBankClient::enSaveResults::svSucceeded:
        {
            std::cout << "\nAccount Added Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            std::cout << "\nError account was not saved because it's Empty";
            break;

        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        {
            std::cout << "\nError account was not saved because account number is used!\n";
            break;

        }
        }
    }



};
