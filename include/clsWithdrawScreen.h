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
		std::cout << "Please Enter Withdraw Amount? ";
		double withdraw = clsInputValidate::ReadFloatNumber();

		char sure = 'Y';
		std::cout << "Are you sure you want to make this withdraw? Y/N  ";
		std::cin >> sure;

		if (toupper(sure) != 'Y')
		{
			return false;
		}

		if (!Client.Withdraw(withdraw))
		{
			std::cout << "\nWithdraw Failed: Amount Exceeds the Available Balance.\n";
			return false;
		}

		return true;
	}

public:
	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t   Withdraw");

		std::string AccountNumber;
		std::cout << "Please enter the AccountNumber?\n";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			std::cout << "The Client Is Not Exist! Please Choose another PinCode:";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		Client.Print();

		if (_AddWithdraw(Client))
		{
			Client.Print();
			std::cout << "\nThe Process Done Successfully ;)\n";
		}
	}

};
