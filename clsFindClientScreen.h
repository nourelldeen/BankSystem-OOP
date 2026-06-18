#pragma once
#include "clsBankClient.h"
#include <iostream>
#include "clsScreen.h"
class clsFindClientScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.GetAccountNumber();
        cout << "\nPin Code    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";
    }

  public:
      static void ShowFindClientScreen()
      {
          if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
          {
              return;// this will exit the function and it will not continue
          }

          _DrawScreenHeader("Find Client");

          string AccountNumber;
          cout << "Please enter the AccountNumber?\n";
          AccountNumber = clsInputValidate::ReadString();

          while (!clsBankClient::IsClientExist(AccountNumber))
          {
              cout << "The Client Is Already Exist! Please Choose another PinCode:";
              AccountNumber = clsInputValidate::ReadString();
          }

          clsBankClient Client = clsBankClient::Find(AccountNumber);



          if (!Client.IsEmpty())
          {
              cout << "\nClient Found :)\n";
          }
          else
          {
              cout << "\nClient Was Not Found :(\n";
          }

          _PrintClient(Client);
      }
};

