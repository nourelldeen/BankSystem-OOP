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
		std::cout << "Please Enter Deposit Amount? ";
		double deposit = clsInputValidate::ReadFloatNumber();

		char sure = 'Y';
		std::cout << "Are you sure you want to add this deposit? Y/N  ";
		std::cin >> sure;

		if (toupper(sure) != 'Y')
		{
			return false;
		}

		Client.Deposit(deposit);
		return true;
	}

public:
	static void ShowDepositScreen()
	{
		_DrawScreenHeader("Deposit");

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

		if (_AddDeposit(Client))
		{
			Client.Print();
			std::cout << "\nThe Process Done Successfully ;)\n";
		}
		else
		{
			std::cout << "\nDeposit Cancelled.\n";
		}
	}

};
