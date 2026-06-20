#pragma once
#include "clsBankClient.h"
#include <iostream>
#include "clsScreen.h"
class clsFindClientScreen : protected clsScreen
{
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

          Client.Print();
      }
};

