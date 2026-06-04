#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"
class clsLoginScreen : public clsScreen
{
private:
	static void _GetUserNameAndPassword(string& UserName, string& Password)
	{
		cout << "Enter User Name? ";
		cin >> UserName;

		cout << "Enter Password? ";
		cin >> Password;

	}
	static void _Login()
	{
		bool LoginFaild = false;

		string Username, Password;
		do
		{

			if (LoginFaild)
			{
				cout << "\nInvlaid Username/Password!\n\n";
			}

			_GetUserNameAndPassword(Username, Password);

			CurrentUser = clsUser::Find(Username, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		clsMainScreen::ShowMainMenue();
	}

public:
	static void ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\t Login");

		_Login();
	}
};

