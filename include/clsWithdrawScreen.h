#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
class clsWithdrawScreen : public clsScreen
{
private:
	static bool _AddWithdraw(clsBankClient& Client)
	{
		cout << "Please Enter Withdraw Amount? ";
		float withdraw = clsInputValidate::ReadFloatNumber();

		char sure = 'Y';
		cout << "Are you sure you want to make this withdraw? Y/N  ";
		cin >> sure;

		if (toupper(sure) != 'Y')
		{
			return false;
		}

		if (!Client.Withdraw(withdraw))
		{
			cout << "\nWithdraw Failed: Amount Exceeds the Available Balance.\n";
			return false;
		}

		return true;
	}

public:
	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t   Withdraw");

		string AccountNumber;
		cout << "Please enter the AccountNumber?\n";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "The Client Is Not Exist! Please Choose another PinCode:";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		Client.Print();

		if (_AddWithdraw(Client))
		{
			Client.Print();
			cout << "\nThe Process Done Successfully ;)\n";
		}
	}

};