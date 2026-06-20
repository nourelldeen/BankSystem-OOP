#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"
class clsLoginScreen : public clsScreen
{
private:
	static void _GetUserNameAndPassword(std::string& UserName, std::string& Password)
	{
		std::cout << "Enter User Name? ";
		std::cin >> UserName;

		std::cout << "Enter Password? ";
		std::cin >> Password;

	}


	static bool _Login()
	{
		bool LoginFaild = false;
		short NumOfTries = 0;

		std::string Username, Password;
		do
		{

			if (LoginFaild)
			{
				NumOfTries++;
				std::cout << "\nInvalid Username/Password!\n\n";
				std::cout << "You have " << (3 - NumOfTries);
				std::cout << " trail(s) to Login.\n";
			}
			if (NumOfTries == 3)
			{
				std::cout << "You are Locked after 3 failed trails.\n\n";
				return false;
			}

			_GetUserNameAndPassword(Username, Password);

			CurrentUser = clsUser::Find(Username, Password);

			LoginFaild = CurrentUser.IsEmpty();
		
		} while (LoginFaild);

		CurrentUser.RegisterLogIn();

		clsMainScreen::ShowMainMenue();
		return true;
	}

public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\t Login");

		return _Login();
	}
};

