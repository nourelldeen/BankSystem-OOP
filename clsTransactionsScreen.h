#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
using namespace std;

class clsTransactionsScreen : protected clsScreen
{
	enum enTransactionsOptions {Deposit = 1,Withdraw = 2, TotalBalance = 3, MainMenu = 4};
    
    static short _ReadTransactionsMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 8]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 8, "Enter Number between 1 to 8? ");
        return Choice;
    }

    static void _PerformTransactionsOption(enTransactionsOptions Options)
    {
        switch (Options)
        {
        case enTransactionsOptions::Deposit:
            // _ShowDepositScreen();
            break;
          
        case enTransactionsOptions::Withdraw:
            // _ShowWithdrawScreen();
            break;


        case enTransactionsOptions::TotalBalance:
            system("cls");
            clsBankClient::PrintClientBalanceList();
            break;

        case enTransactionsOptions::MainMenu:
            clsMainScreen::ShowMainMenue();
            break;
        }
    }

public:
    
    static void ShowTransactionsMenu()
    {
        _DrawScreenHeader("Transactions Screen");
       
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tTransactions Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 4]: ";

        _PerformTransactionsOption((enTransactionsOptions)_ReadTransactionsMenuOption());
           
    }

};

