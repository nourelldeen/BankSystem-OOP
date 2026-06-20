#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsUser.h"


class clsLoginRegisterScreen :protected clsScreen
{

private:

    static void PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
    {

        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(35) << std::left << LoginRegisterRecord.DateTime;
        std::cout << "| " << std::setw(20) << std::left << LoginRegisterRecord.UserName;
        std::cout << "| " << std::setw(20) << std::left << LoginRegisterRecord.Password;
        std::cout << "| " << std::setw(10) << std::left << LoginRegisterRecord.Permissions;
    }

public:

    static void ShowLoginRegisterScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pShowLogInRegister))
        {
            return;
        }

        std::vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();

        std::string Title = "\tLogin Register List Screen";
        std::string SubTitle = "\t\t(" + std::to_string(vLoginRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;

        std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(35) << "Date/Time";
        std::cout << "| " << std::left << std::setw(20) << "UserName";
        std::cout << "| " << std::left << std::setw(20) << "Password";
        std::cout << "| " << std::left << std::setw(10) << "Permissions";
        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;

        if (vLoginRegisterRecord.size() == 0)
            std::cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsUser::stLoginRegisterRecord Record : vLoginRegisterRecord)
            {

                PrintLoginRegisterRecordLine(Record);
                std::cout << std::endl;
            }

        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_________________________________________\n" << std::endl;

    }

};
