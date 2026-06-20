#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>


class clsClientListScreen :protected clsScreen
{

private:
    static void _PrintClientListHeader()
    {
        std::cout << "____________________________________________________________________________________________________________________\n\n";
        std::cout << std::setw(20) << std::left << "| Account Number";
        std::cout << std::setw(20) << std::left << "| Pin Code";
        std::cout << std::setw(40) << std::left << "| Client Name";
        std::cout << std::setw(20) << std::left << "| Phone";
        std::cout << std::setw(20) << std::left << "| Balance";
        std::cout << "\n____________________________________________________________________________________________________________________\n\n";
    }

    static void _PrintListInfo(clsBankClient Client)
    {
        std::cout << "| " << std::setw(18) << Client.GetAccountNumber();
        std::cout << "| " << std::setw(18) << Client.GetPinCode();
        std::cout << "| " << std::setw(38) << Client.FullName();
        std::cout << "| " << std::setw(18) << Client.GetPhone();
        std::cout << "| " << std::setw(18) << Client.GetAccountBalance();
    }

public:
    static void ShowClientList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pListClients))
        {
            return;// this will exit the function and it will not continue
        }

        std::vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        std::string Title = "\t  Client List Screen";
        std::string SubTitle = "\t    (" + std::to_string(vClients.size()) + ") Client(s).";

        system("cls");

        _DrawScreenHeader(Title, SubTitle);
        _PrintClientListHeader();
        if (vClients.size() == 0)
            std::cout << "\t\t\t\tNo Clients Available In the System!";
        else

        for (clsBankClient& Client : vClients)
        {
            _PrintListInfo(Client);
        }
        std::cout << "\n____________________________________________________________________________________________________________________\n\n\n";

    }

};

