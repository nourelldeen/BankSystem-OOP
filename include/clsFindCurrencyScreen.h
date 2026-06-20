#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen :protected clsScreen
{

private:
    static void _PrintCurrency(clsCurrency Currency)
    {
        std::cout << "\nCurrency Card:\n";
        std::cout << "_____________________________\n";
        std::cout << "\nCountry    : " << Currency.Country();
        std::cout << "\nCode       : " << Currency.CurrencyCode();
        std::cout << "\nName       : " << Currency.CurrencyName();
        std::cout << "\nRate(1$) = : " << Currency.Rate();

        std::cout << "\n_____________________________\n";

    }

    static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            std::cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            std::cout << "\nCurrency Was not Found :-(\n";
        }
    }

public:

    static void ShowFindCurrencyScreen()
    {

        _DrawScreenHeader("\t  Find Currency Screen");

        std::cout << "\nFind By: [1] Code or [2] Country ? ";
        short Answer = 1;

        std::cin >> Answer;

        if (Answer == 1)
        {
            std::string CurrencyCode;
            std::cout << "\nPlease Enter CurrencyCode: ";
            CurrencyCode = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);
        }
        else
        {
            std::string Country;
            std::cout << "\nPlease Enter Country Name: ";
            Country = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);
        }






    }

};
