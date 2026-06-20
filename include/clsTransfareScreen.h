#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen :protected clsScreen
{

private:
    static void _PrintClient(clsBankClient Client)
    {
        std::cout << "\nClient Card:";
        std::cout << "\n___________________\n";
        std::cout << "\nFull Name   : " << Client.FullName();
        std::cout << "\nAcc. Number : " << Client.GetAccountNumber();
        std::cout << "\nBalance     : " << Client.AccountBalance;
        std::cout << "\n___________________\n";

    }

    static std::string _ReadAccountNumber(std::string Prompt)
    {
        std::string AccountNumber;
        std::cout << Prompt;

        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            std::cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }

    static float _ReadAmount(clsBankClient SourceClient)
    {
        float Amount;

        std::cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidate::ReadFloatNumber();

        while (Amount > SourceClient.AccountBalance)
        {
            std::cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }

public:

    static void ShowTransferScreen()
    {

        _DrawScreenHeader("\tTransfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer From: "));

        _PrintClient(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer To: "));

        _PrintClient(DestinationClient);

        float Amount = _ReadAmount(SourceClient);


        std::cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        std::cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
            {
                std::cout << "\nTransfer done successfully\n";
            }
            else
            {
                std::cout << "\nTransfer Faild \n";
            }
        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);

    }

};
