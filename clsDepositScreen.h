#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
class clsDepositScreen : public clsScreen
{
private:

	static bool _AddDeposit(clsBankClient& Client)
	{
		cout << "Please Enter Deposit Amount? ";
		float deposit = clsInputValidate::ReadFloatNumber();

		char sure = 'Y';
		cout << "Are you sure you want to add this deposit? Y/N  ";
		cin >> sure;

		if (toupper(sure) != 'Y')
		{
			return false;
		}

		Client.Deposit(deposit);
		return true;
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

		if (_AddDeposit(Client))
		{
			_Print(Client);
			cout << "\nThe Process Done Successfully ;)\n";
		}
		else
		{
			cout << "\nDeposit Cancelled.\n";
		}
	}

};