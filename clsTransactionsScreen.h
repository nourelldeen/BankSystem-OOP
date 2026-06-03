#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanceScreen.h"

using namespace std;


class clsTransactionsScreen : protected clsScreen
{
	enum enTransactionsOptions {Deposit = 1,Withdraw = 2, TotalBalance = 3, MainMenu = 4};
    
    static short _ReadTransactionsMenuOption()
    {
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 4);
        return Choice;
    }

    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();

    }


    static void _PerformTransactionsOption(enTransactionsOptions Options)
    {
        switch (Options)
        {
        case enTransactionsOptions::Deposit:
            system("cls");
            clsDepositScreen::ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
          
        case enTransactionsOptions::Withdraw:
            system("cls");
            clsWithdrawScreen::ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;


        case enTransactionsOptions::TotalBalance:
            system("cls");
            clsTotalBalanceScreen::PrintClientBalanceList();
            _GoBackToTransactionsMenue();
            break;

        case enTransactionsOptions::MainMenu:
            //I will return to the Main Menu automatically 
            break;
        }
    }

public:
    
    static void ShowTransactionsMenue()
    {
        system("cls");
        _DrawScreenHeader("\tTransactions Screen");
       
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t Transactions Menu\n";
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
