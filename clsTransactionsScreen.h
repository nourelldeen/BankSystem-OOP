#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsTransfareScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;


class clsTransactionsScreen : protected clsScreen
{
    enum enTransactionsOptions
    {
        eDeposit = 1,
        eWithdraw = 2,
        eTotalBalance = 3,
        eTransfare = 4,
        eTransfareLog = 5,
        eMainMenu = 6
    };
    

    static short _ReadTransactionsMenuOption()
    {
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 6);
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
        case enTransactionsOptions::eDeposit:
            system("cls");
            clsDepositScreen::ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
          
        case enTransactionsOptions::eWithdraw:
            system("cls");
            clsWithdrawScreen::ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;


        case enTransactionsOptions::eTotalBalance:
            system("cls");
            clsTotalBalanceScreen::PrintClientBalanceList();
            _GoBackToTransactionsMenue();
            break;
        case enTransactionsOptions::eTransfare:
            system("cls");
            clsTransferScreen::ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;
        case enTransactionsOptions::eTransfareLog:
            system("cls");
            clsTransferLogScreen::ShowTransferLogScreen();
            _GoBackToTransactionsMenue();
            break;

        case enTransactionsOptions::eMainMenu:
            //I will return to the Main Menu automatically 
            break;
        }
    }

public:
    
    static void ShowTransactionsMenue()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            return;// this will exit the function and it will not continue
        }
        system("cls");
        _DrawScreenHeader("\tTransactions Screen");
       
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t Transactions Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfare.\n";
        cout << setw(37) << left << "" << "\t[5] TransfareLog.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]: ";

        _PerformTransactionsOption((enTransactionsOptions)_ReadTransactionsMenuOption());
           
    }  
};
