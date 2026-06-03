#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
class clsDepositScreen : public clsScreen
{
private:

	static void _AddDeposit(clsBankClient& Client)
	{
		float deposit = 0.0;
		cout << "Please Enter Deposit Amount? ";
		cin >> deposit;

		char sure = 'Y';
		cout << "Are you sure you want to add this deposit? Y/N  ";
		cin >> sure;

		if (toupper(sure) == 'Y')
		{
			Client.AccountBalance += deposit;
		}
	}

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
	static void ShowDepositScreen()
	{
		_DrawScreenHeader("Deposit");

		string AccountNumber;
		cout << "Please enter the AccountNumber?\n";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "The Client Is Not Exist! Please Choose another PinCode:";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_Print(Client);

		_AddDeposit(Client);
		Client.Save();

		_Print(Client);

		cout << "\nThe Process Done Successfully ;)\n";
	}

};

