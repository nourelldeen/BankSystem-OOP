#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
class clsUpdateClientData : public clsScreen
{
private :
    static void _Print(clsBankClient& client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.FirstName;
        cout << "\nLastName    : " << client.LastName;
        cout << "\nFull Name   : " << client.FullName();
        cout << "\nEmail       : " << client.Email;
        cout << "\nPhone       : " << client.Phone;
        cout << "\nAcc. Number : " << client.GetAccountNumber();
        cout << "\nPin Code    : " << client.GetPinCode();
        cout << "\nBalance     : " << client.GetAccountBalance();
        cout << "\n___________________\n";
    }
public:
    static	void UpdateClientData()
    {
        _DrawScreenHeader("\tUpdate Client's Data Screen");
        string AccountNumber;
        vector <clsBankClient> vFileData = clsBankClient::GetDataFromFileToVector();

        cout << "Please Enter The Account Number?\n";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "The Client Is NOT Exist! Please try again?\n";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _Print(Client);

        char Sure = 'N';

        cout << "\nAre you sure you want to update this account?  Y/N: ";
        cin >> Sure;

        if (toupper(Sure) == 'Y')
        {
            clsBankClient UpdatedClient = clsBankClient::UpdateClientDataInVector(vFileData, AccountNumber);
            clsBankClient::UploadDataToFile(vFileData);
            _Print(UpdatedClient);

            cout << "The Client updated successfully :) \n";
        }
        else
            cout << "The Client wasn't updateed \n";
    }

};

