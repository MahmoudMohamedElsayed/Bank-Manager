#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{

private:

	static bool _Login()
	{
		bool LoginFaild = false;
		short FaildLoginCount = 0;

		string UserName, Password;

		do
		{

			if (LoginFaild)
			{
				FaildLoginCount++;

				cout << "\nInvalid UserName/Password\n";
				cout << "You have " << (3 - FaildLoginCount)
					 << " Trial(s) to login.\n\n";
				
				if (FaildLoginCount == 3)
				{
					cout << "\nYour are Locked after 3 faild trials\n";
					return false;
				}
			}

			cout << "Enter UserName? ";
			UserName = clsInputValidate<string>::ReadString();
			cout << "Enter Password? ";
			Password = clsInputValidate<string>::ReadString();

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
	}


public:

	/*static void ShowLoginScreen()
	{
		string UserName, Password;
		bool isExist = true;

		do
		{
			system("cls");
			_DrawScreenHeader("\t  Login Screen");

			if (!isExist)  cout << "\nInvalid UserName/Password\n";

			cout << "\nEnter UserName? ";
			UserName = clsInputValidate::ReadString();
			cout << "Enter Password? ";
			Password = clsInputValidate::ReadString();


			isExist = clsUser::IsUserExist(UserName, Password);

		} while (!isExist);

		clsMainScreen::ShowMainMenue();
	}*/

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t   Login Screen");
		return _Login();
	}

};

