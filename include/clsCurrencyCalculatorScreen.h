#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen :protected clsScreen

{
private:

    static double _ReadAmount()
    {
        std::cout << "\nEnter Amount to Exchange: ";
        double Amount = 0;

        Amount = clsInputValidate::ReadFloatNumber();
        return Amount;
    }

    static clsCurrency _GetCurrency(std::string Message)
    {

        std::string CurrencyCode;
        std::cout << Message << std::endl;
        
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            std::cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;
    }


    static  void _PrintCurrencyCard(clsCurrency Currency, std::string Title = "Currency Card:")
    {

        std::cout << "\n" << Title << "\n";
        std::cout << "_____________________________\n";
        std::cout << "\nCountry       : " << Currency.Country();
        std::cout << "\nCode          : " << Currency.CurrencyCode();
        std::cout << "\nName          : " << Currency.CurrencyName();
        std::cout << "\nRate(1$) =    : " << Currency.Rate();
        std::cout << "\n_____________________________\n\n";

    }

    static void _PrintCalculationsResults(double Amount, clsCurrency Currency1, clsCurrency Currency2)
    {

        _PrintCurrencyCard(Currency1, "Convert From:");

        double AmountInUSD = Currency1.ConvertToUSD(Amount);

        std::cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInUSD << " USD\n";

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }

        std::cout << "\nConverting from USD to:\n";

        _PrintCurrencyCard(Currency2, "To:");

        double AmountInCurrrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

        std::cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInCurrrency2 << " " << Currency2.CurrencyCode();

    }
public:

    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'y';

        while (Continue == 'y' || Continue == 'Y')
        {
            system("cls");

            _DrawScreenHeader("\tUpdate Currency Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            double Amount = _ReadAmount();

            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            std::cout << "\n\nDo you want to perform another calculation? y/n ? ";
            std::cin >> Continue;

        }


    }
};
