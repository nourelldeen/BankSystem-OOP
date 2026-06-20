#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

class clsCurrenciesListScreen :protected clsScreen
{

private:
    static void PrintCurrencyRecordLine(clsCurrency Currency)
    {

        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(30) << std::left << Currency.Country();
        std::cout << "| " << std::setw(8) << std::left << Currency.CurrencyCode();
        std::cout << "| " << std::setw(45) << std::left << Currency.CurrencyName();
        std::cout << "| " << std::setw(10) << std::left << Currency.Rate();

    }

public:


    static void ShowCurrenciesListScreen()
    {


        std::vector <clsCurrency> vCurrencys = clsCurrency::GetCurrenciesList();
        std::string Title = "\t  Currencies List Screen";
        std::string SubTitle = "\t    (" + std::to_string(vCurrencys.size()) + ") Currency.";

        _DrawScreenHeader(Title, SubTitle);
        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_______________________________________________\n" << std::endl;

        std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(30) << "Country";
        std::cout << "| " << std::left << std::setw(8) << "Code";
        std::cout << "| " << std::left << std::setw(45) << "Name";
        std::cout << "| " << std::left << std::setw(10) << "Rate/(1$)";
        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_______________________________________________\n" << std::endl;

        if (vCurrencys.size() == 0)
            std::cout << "\t\t\t\tNo Currencies Available In the System!";
        else

            for (clsCurrency Currency : vCurrencys)
            {

                PrintCurrencyRecordLine(Currency);
                std::cout << std::endl;
            }

        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_______________________________________________\n" << std::endl;

    }

};
